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

#ifndef SRC_KMER_COLLECTION_H_
#define SRC_KMER_COLLECTION_H_

#include <string>
#include <cstdint>
#include <iterator>
#include <memory>

class KmerCollection {

  class KmerIterator : public std::iterator<std::bidirectional_iterator_tag, uint_fast64_t>
  {
   public:
    KmerIterator(KmerCollection* owner, int position) :
    m_owner(owner),
    m_position(position)
    {}

    KmerIterator(const KmerIterator& other, int position) :
      m_owner(other.m_owner),
      m_position(position)
    {}

    KmerIterator& operator=(const KmerIterator& other) {
    if(this != &other) {
        m_owner = other.m_owner;
        m_position = other.m_position;
      }
      return *this;
    }

    bool operator==(const KmerIterator& other) {
      return m_owner == other.m_owner &&
             m_position == other.m_position;
    }

    bool operator!=(const KmerIterator& other) {
      return !(*this == other);
    }

    uint_fast64_t& operator*() {
      return m_owner->m_kmerList[m_position];
    }

    uint_fast64_t* operator->() {
      return &m_owner->m_kmerList[m_position];
    }

    KmerIterator operator++() {
      m_position++;
      return *this;
    }

    KmerIterator operator++(int) {
      const KmerIterator clone(*this);
      ++(*this);
      return clone;
    }

    KmerIterator operator--() {
      m_position--;
      return *this;
    }

    KmerIterator operator--(int) {
      const KmerIterator clone(*this);
      --(*this);
      return clone;
    }

   private:
    KmerCollection* m_owner;
    int m_position;
  };

 public:
  typedef KmerIterator iterator;

  // Copying KmerCollection is not allowed, use std::move instead.
  KmerCollection(const KmerCollection&) = delete;
  KmerCollection& operator=(const KmerCollection&) = delete;

  KmerCollection(const std::shared_ptr<std::string> seqEntry,
                 int kmerSize, int scoreMin,
                 int stepSize = 1, bool compressHint = true) :
    m_seqEntry(seqEntry),
    m_kmerSize(kmerSize),
    m_stepSize(scoreMin),
    m_scoreMin(stepSize),
    m_kmerListSize(seqEntry->size() - kmerSize + 1),
    m_kmerList(nullptr),
    m_usedGenerator(&KmerCollection::generateKmersN),
    m_compress(compressHint)
  {
    if(m_compress == false && kmerSize > 8) {
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
    m_usedGenerator(&KmerCollection::generateKmersN),
    m_compress(std::move(other.m_compress))
  {}

  virtual ~KmerCollection() {
    if(m_kmerList) {
      delete[] m_kmerList;
    }
  }

  KmerCollection::iterator begin() {
    if(m_kmerList == nullptr) {
      chooseGenerator();

      m_kmerList = new uint_fast64_t[m_kmerListSize];
      const char* ptr = m_seqEntry->data();

      for(int i = 0; i < m_kmerListSize; ++i) {
        m_kmerList[i] = (this->*m_usedGenerator)(&(ptr[i]));
      }
    }
    return KmerIterator(this, 0);
  }

  KmerCollection::iterator end() {
    return KmerIterator(this, m_kmerListSize);
  }

 private:
  void chooseGenerator() {
    if(m_compress == false) switch(m_kmerSize) {
      case 8: m_usedGenerator = &KmerCollection::generateUncompressedKmers8; break;
      default: m_usedGenerator = &KmerCollection::generateUncompressedKmersN; break;
    }
    else switch(m_kmerSize) {
      case 8: m_usedGenerator = &KmerCollection::generateKmers8; break;
      default: m_usedGenerator = &KmerCollection::generateKmersN; break;
    }
  }

  // This assumes the next 8 chars is readable
  uint_fast64_t generateKmers8(const char* ptr) {
    uint_fast64_t kmer = *(const uint_fast64_t*)ptr;
    kmer >>= 1; // 00000110 => 00000011
    kmer |= kmer >> 30; // 00001111
    kmer |= kmer >> 12; // 11111111
    return kmer;
  }

  // This assumes the next N chars is readable
  uint_fast64_t generateKmersN(const char* ptr) {
    uint_fast64_t kmer = (ptr[0] >> 1) & 3;
    for(int i = 1; i < m_kmerSize; ++i) {
      kmer |= (ptr[i] & 6) << (i*2-1);
    }
    return kmer;
  }

  // This assumes the next N chars is readable
  uint_fast64_t generateUncompressedKmers8(const char* ptr) {
    return *(const uint_fast64_t*)ptr;
  }

  // This assumes the next N chars is readable, and N < 8
  uint_fast64_t generateUncompressedKmersN(const char* ptr) {
    uint_fast64_t kmer = *(const uint_fast64_t*)ptr;
    kmer >>= (8 - m_kmerSize) << 8;
    return kmer;
  }

 private:
  const std::shared_ptr<std::string> m_seqEntry; // TODO: change string to SeqEntry class
  int m_kmerSize; // K
  int m_stepSize;
  int m_scoreMin;

  int m_kmerListSize;
  uint_fast64_t* m_kmerList;
  uint_fast64_t (KmerCollection::*m_usedGenerator)(const char*);

  bool m_compress;
};

#endif // SRC_KMER_COLLECTION_H_
