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

  KmerCollection(const std::string* seqEntry, int kmerSize, int scoreMin, int stepSize = 1) :
    m_seqEntry(seqEntry),
    m_kmerSize(kmerSize),
    m_stepSize(scoreMin),
    m_scoreMin(stepSize),
    m_kmerListProgress(-1),
    m_kmerListSize(seqEntry->size() - kmerSize + 1),
    m_kmerList(nullptr)
  {}

  KmerCollection(KmerCollection&& other) :
    m_seqEntry(std::move(other.m_seqEntry)),
    m_kmerSize(std::move(other.m_kmerSize)),
    m_stepSize(std::move(other.m_stepSize)),
    m_scoreMin(std::move(other.m_scoreMin)),
    m_kmerListProgress(std::move(other.m_kmerListProgress)),
    m_kmerListSize(std::move(other.m_kmerListSize)),
    m_kmerList(std::move(other.m_kmerList))
  {
    other.m_kmerList = nullptr;
  }

  virtual ~KmerCollection() {
    if(m_kmerList) {
      delete[] m_kmerList;
    }
  }

  KmerCollection::iterator begin() {
    if(m_kmerList == nullptr) {
      uint_fast64_t (KmerCollection::*)(const char*) fun;
      switch(m_kmerSize) {
        case 8: fun = generateKmers8; break;
        default: fun = generateKmersN; break;
      }

      m_kmerList = new uint_fast64_t[m_kmerListSize];
      const char* ptr = m_seqEntry.data();

      for(int i = 0; i < m_kmerListSize; ++i) {
        m_kmerList[i] = generateKmersN(&(ptr[i]));
      }
    }
    return KmerIterator(this, 0);
  }

  KmerCollection::iterator end() {
    return KmerIterator(this, m_kmerListSize);
  }

 private:
  // This assumes the next 8 chars is readable
  inline uint_fast64_t generateKmers8(const char* ptr) {
    uint_fast64_t kmer = *((const uint_fast64_t*)ptr);
    kmer >>= 1; // 00000110 => 00000011
    kmer |= kmer >> 30; // 00001111
    kmer |= kmer >> 12; // 11111111
    return kmer;
  }

  // This assumes the next N chars is readable
  inline uint_fast64_t generateKmersN(const char* ptr) {
    uint_fast64_t kmer = (ptr[0] >> 1) & 3;
    for(int i = 1; i < m_kmerSize; ++i) {
      kmer |= (ptr[i] & 6) << (i*2-1);
    }
    return 0;
  }

 private:
  const std::string* m_seqEntry; // TODO: change string to SeqEntry class
  int m_kmerSize; // K
  int m_stepSize;
  int m_scoreMin;

  int m_kmerListProgress; // How much of kmerList has been generated
  int m_kmerListSize;
  uint_fast64_t* m_kmerList;
};

#endif // SRC_KMER_COLLECTION_H_
