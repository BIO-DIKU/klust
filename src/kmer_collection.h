/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

#ifndef KLUST_KMER_COLLECTION_H_
#define KLUST_KMER_COLLECTION_H_

#include <string>
#include <cstdint>
#include <iterator>
#include <memory>

#include <BioIO/seq_entry.h>

class KmerCollection {

  class KmerIterator : public std::iterator<std::bidirectional_iterator_tag, uint_fast64_t>
  {
   public:
    KmerIterator(KmerCollection* owner, size_t position) :
    m_owner(owner),
    m_position(position)
    {}

    KmerIterator(const KmerIterator& other) :
      m_owner(other.m_owner),
      m_position(other.m_position)
    {}

    /**
    * Assignment operator.
    */
    KmerIterator& operator=(const KmerIterator& other) {
    if(this != &other) {
        m_owner = other.m_owner;
        m_position = other.m_position;
      }
      return *this;
    }

    /**
    * Comparison operator.
    */
    bool operator==(const KmerIterator& other) {
      return m_owner == other.m_owner &&
             m_position == other.m_position;
    }

    /**
    * Comparison operator.
    */
    bool operator!=(const KmerIterator& other) {
      return !(*this == other);
    }

    /**
    * Dereference operator.
    */
    uint_fast64_t& operator*() {
      return m_owner->m_kmerList[m_position];
    }

    /**
    * Dereference operator.
    */
    uint_fast64_t* operator->() {
      return &m_owner->m_kmerList[m_position];
    }

    /**
    * Increment iterator.
    */
    KmerIterator operator++() {
      ++m_position;
      return *this;
    }

    /**
    * Increment iterator.
    */
    KmerIterator operator++(int) {
      const KmerIterator clone(*this);
      ++(*this);
      return clone;
    }

    /**
    * Decrement iterator.
    */
    KmerIterator operator--() {
      --m_position;
      return *this;
    }

    /**
    * Decrement iterator.
    */
    KmerIterator operator--(int) {
      const KmerIterator clone(*this);
      --(*this);
      return clone;
    }

   private:
    KmerCollection* m_owner;
    size_t m_position;
  };

 public:
  typedef KmerIterator iterator;

  // Copying KmerCollection is not allowed, use std::move instead.
  KmerCollection(const KmerCollection&) = delete;
  KmerCollection& operator=(const KmerCollection&) = delete;

  KmerCollection(const std::shared_ptr<SeqEntry> seqEntry,
                 int kmerSize, int scoreMin,
                 int stepSize = 1, bool compressHint = true) :
    m_seqEntry(seqEntry),
    m_kmerSize(kmerSize),
    m_stepSize(stepSize),
    m_scoreMin(scoreMin),
    m_kmerListSize(0),
    m_kmerList(nullptr),
    m_usedGenerator(&KmerCollection::generateKmerN),
    m_compress(compressHint)
  {
    if(!m_compress && kmerSize > 8) {
      m_compress = true;
    }
  }

  KmerCollection(KmerCollection&& other) :
    m_seqEntry(std::move(other.m_seqEntry)),
    m_kmerSize(std::move(other.m_kmerSize)),
    m_stepSize(std::move(other.m_stepSize)),
    m_scoreMin(std::move(other.m_scoreMin)),
    m_kmerListSize(std::move(other.m_kmerListSize)),
    m_kmerList(std::move(other.m_kmerList)),
    m_usedGenerator(&KmerCollection::generateKmerN),
    m_compress(std::move(other.m_compress))
  {
    other.m_kmerList = nullptr;
  }

  /**
  * Generates kmers if necessary.
  * \return Number of kmers.
  */
  size_t size() {
    generateKmers();
    return m_kmerListSize;
  }

  /**
  * Generates kmers if necessary.
  * \return Iterator to KmerCollection's first element.
  */
  KmerCollection::iterator begin() {
    generateKmers();
    return KmerIterator(this, 0);
  }

  /**
  * \return Iterator to the element after KmerCollection's last element.
  */
  inline KmerCollection::iterator end() {
    generateKmers();
    return KmerIterator(this, m_kmerListSize);
  }

 private:
  inline void generateKmers() {
    if(m_kmerList == nullptr) {
      chooseGenerator();

      m_kmerListSize = (m_seqEntry->seq().size() - m_kmerSize) / m_stepSize + 1;

      m_kmerList = std::unique_ptr<uint_fast64_t[]>(new uint_fast64_t[m_kmerListSize]);
      const char* ptr = m_seqEntry->seq().data();

      for(size_t i = 0; i < m_kmerListSize; ++i) {
        m_kmerList[i] = (this->*m_usedGenerator)(&(ptr[i*m_stepSize]));
      }
    }
  }

  inline void chooseGenerator() {
    if(!m_compress) switch(m_kmerSize) {
      case 8: m_usedGenerator = &KmerCollection::generateUncompressedKmer8; break;
      default: m_usedGenerator = &KmerCollection::generateUncompressedKmerN; break;
    }
    else switch(m_kmerSize) {
      case 8: m_usedGenerator = &KmerCollection::generateKmer8; break;
      default: m_usedGenerator = &KmerCollection::generateKmerN; break;
    }
  }

  // This assumes the next 8 chars is readable
  uint_fast64_t generateKmer8(const char* ptr) const {
    const uint_fast64_t mask = 0x0606060606060606;
    uint64_t kmer = *(const uint64_t*)ptr & mask;
    kmer >>= 1; // 00000110 => 00000011
    kmer |= kmer >> 30; // 00001111
    kmer |= kmer >> 12; // 11111111
    return static_cast<uint_fast64_t>(kmer & 0xFFFF);
  }

  // This assumes the next N chars is readable
  uint_fast64_t generateKmerN(const char* ptr) const {
    uint_fast64_t kmer = (ptr[0] >> 1) & 3;
    for(int i = 1; i < m_kmerSize; ++i) {
      kmer |= (ptr[i] & 6) << (i*2-1);
    }
    return kmer;
  }

  // This assumes the next N chars is readable
  uint_fast64_t generateUncompressedKmer8(const char* ptr) const {
    return static_cast<uint_fast64_t>(*(const uint64_t*)ptr);
  }

  // This assumes the next N chars is readable, and N < 8
  uint_fast64_t generateUncompressedKmerN(const char* ptr) const {
    uint64_t kmer = *(const uint64_t*)ptr;
    kmer >>= (8 - m_kmerSize) << 8;
    return static_cast<uint_fast64_t>(kmer);
  }

 private:
  const std::shared_ptr<SeqEntry> m_seqEntry;
  int m_kmerSize; // K
  int m_stepSize;
  int m_scoreMin;

  size_t m_kmerListSize;
  std::unique_ptr<uint_fast64_t[]> m_kmerList;
  uint_fast64_t (KmerCollection::*m_usedGenerator)(const char*)const;

  bool m_compress;
};

#endif // KLUST_KMER_COLLECTION_H_
