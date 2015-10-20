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

#define A_ "00"
#define C_ "01"
#define G_ "11"
#define T_ "10"

#include "catch.hpp"

#include "../src/kmer_collection.h"

#include <bitset>
#include <memory>
#include <string>
#include <sstream>
#include <memory>

TEST_CASE("Basic functionalities of kmer_collection", "[kmer_collection]") {
  SeqEntry s("name", "caaatcgcgggatttcgaaactatggg", {}, SeqEntry::SeqType::nucleotide);
  std::shared_ptr<SeqEntry> p = std::make_shared<SeqEntry>(s);
  KmerCollection collection(p, 8, 1);

  auto itBegin = collection.begin();
  auto itEnd = collection.end();

  SECTION("Inequality of different objects should be true") {
    REQUIRE(itBegin != itEnd);
  }

  SECTION("Equality of the same object should be the same") {
    REQUIRE(itBegin == itBegin);
    REQUIRE(itEnd == itEnd);
  }

  SECTION("size() should return correct size") {
    REQUIRE(collection.size() == 20);
  }
}


TEST_CASE("All possible generated kmers are unique", "[kmer_collection]") {
  const char ascii[] = {'a', 'c', 't', 'g'};

  int ksize = 8;
  int kmerNum = 1 << (2 * ksize);

  std::stringstream ss;
  std::unique_ptr<int[]> kmer_counter(new int[kmerNum]);

  // Generate sequence string with all possible permutations of k=8
  for(int n = 0; n < kmerNum; ++n) {
    int tmp = n;
    for(int k = 0; k < ksize; ++k) {
      ss << ascii[tmp & 3];
      tmp >>= 2;
    }
  }
  std::string sequence = ss.str();

  // Put sequence string into SeqEntry
  SeqEntry s("name", sequence, {}, SeqEntry::SeqType::nucleotide);
  std::shared_ptr<SeqEntry> p = std::make_shared<SeqEntry>(s);
  KmerCollection collection(p, ksize, 1, ksize, true);

  // Initialize kmer_counter with zeros.
  for(int i = 0; i < kmerNum; ++i) {
    kmer_counter[i] = 0;
  }

  // Count kmers.
  for(KmerCollection::iterator it = collection.begin(); it != collection.end(); ++it) {
    kmer_counter[*it]++;
  }

  int allIsCool = 0;
  for(int i = 0; i < kmerNum; ++i) {
    INFO( "index: i = " << i );
    REQUIRE(kmer_counter[i] == 1);
  }

  REQUIRE(*(collection.begin()) == 0);
  REQUIRE(*(--collection.end()) == kmerNum-1);
}

TEST_CASE("Basic KmerIterator functionality for k = 3", "[kmer_collection]") {
  SeqEntry s("name", "ctgta", {}, SeqEntry::SeqType::nucleotide);
  std::shared_ptr<SeqEntry> p = std::make_shared<SeqEntry>(s);
  KmerCollection collection(p, 3, 1);

  auto it = collection.begin();

  SECTION("KmerIterator can be {in,de}cremented until reaching {end,begin}") {
    REQUIRE(*it == (std::bitset<64>(G_ T_ C_)).to_ulong());
    ++it;
    REQUIRE(*it == (std::bitset<64>(T_ G_ T_)).to_ulong());
    ++it;
    REQUIRE(*it == (std::bitset<64>(A_ T_ G_)).to_ulong());
    ++it;

    REQUIRE(it == collection.end());

    --it;
    REQUIRE(*it == (std::bitset<64>(A_ T_ G_)).to_ulong());
    --it;
    REQUIRE(*it == (std::bitset<64>(T_ G_ T_)).to_ulong());
    --it;
    REQUIRE(*it == (std::bitset<64>(G_ T_ C_)).to_ulong());

    REQUIRE(it == collection.begin());
  }
}
