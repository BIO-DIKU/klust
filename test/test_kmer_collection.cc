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

#include <catch.hpp>

#include "../src/kmer_collection.h"

#include <bitset>
#include <memory>
#include <string>

TEST_CASE("Basic functionalities of kmer_collection", "[kmer_collection]") {
  SeqEntry s("name", "caaatcgcgggatttcgaaactatggg", {}, SeqEntry::SeqType::nucleotide);
  std::shared_ptr<SeqEntry> p = std::make_shared<SeqEntry>(s);
  KmerCollection collection(p, 8, 1);

  auto itBegin = collection.begin();
  auto itEnd = collection.end();

  SECTION("Begin not equal end") {
    REQUIRE(itBegin != itEnd);
  }

  SECTION("comparison for equality") {
    REQUIRE(itBegin == itBegin);
    REQUIRE(itEnd == itEnd);
  }
}

TEST_CASE("Basic KmerIterator functionality for k = 5", "[kmer_collection]") {
  SeqEntry s("name", "caaatcgcgggatttcgaaactatggg", {}, SeqEntry::SeqType::nucleotide);
  std::shared_ptr<SeqEntry> p = std::make_shared<SeqEntry>(s);
  KmerCollection collection(p, 5, 1);

  auto it = collection.begin();

  SECTION("KmerIterator can be incremented and decremented") {
    REQUIRE(*it == (std::bitset<64>(T_ A_ A_ A_ C_)).to_ulong());
    ++it;
    REQUIRE(*it == (std::bitset<64>(C_ T_ A_ A_ A_)).to_ulong());
    ++it;
    REQUIRE(*it == (std::bitset<64>(G_ C_ T_ A_ A_)).to_ulong());
    ++it;
    REQUIRE(*it == (std::bitset<64>(C_ G_ C_ T_ A_)).to_ulong());
    ++it;
    REQUIRE(*it == (std::bitset<64>(G_ C_ G_ C_ T_)).to_ulong());

    --it;
    REQUIRE(*it == (std::bitset<64>(C_ G_ C_ T_ A_)).to_ulong());
    --it;
    REQUIRE(*it == (std::bitset<64>(G_ C_ T_ A_ A_)).to_ulong());
    --it;
    REQUIRE(*it == (std::bitset<64>(C_ T_ A_ A_ A_)).to_ulong());
    --it;
    REQUIRE(*it == (std::bitset<64>(T_ A_ A_ A_ C_)).to_ulong());
  }
}
