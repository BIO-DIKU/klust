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

#include "../catch.hpp"

#include "../../src/modules/kmer_comparison.cc"

TEST_CASE("simple test of comparison", "[kmer_comparison]") {
  SeqEntry s("name", "ACAG", {}, SeqEntry::SeqType::nucleotide);
  SeqEntry t("name", "GACATA", {}, SeqEntry::SeqType::nucleotide);

  KmerComparison compare(2, 1);
  compare.setIdentity(0.9);

  SECTION("s and t should have similarity approx 2/3") {
    REQUIRE(compare.Similarity(s, t) == Approx(2.0/3.0));
  }
  SECTION("s and t should have similarity < threshold") {
    REQUIRE(!compare.Compare(s, t));
  }
}

TEST_CASE("comparison of shorter sequence which is infix of longer sequence", "[kmer_comparison]") {
  SeqEntry s("name", "ACTG", {}, SeqEntry::SeqType::nucleotide);
  SeqEntry t("name", "GACTGA", {}, SeqEntry::SeqType::nucleotide);

  KmerComparison compare(2, 1);
  compare.setIdentity(0.9);

  SECTION("s and t should have identity 1.0") {
    REQUIRE(compare.Similarity(s, t) == Approx(1.0));
  }
  SECTION("s and t should have similarity >= threshold") {
    REQUIRE(compare.Compare(s, t));
  }
}
