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
#include <string>

#include "../../src/modules/levenshtein.cc"

TEST_CASE("Levenshtein returns a correct result after comparison", "[levenshtein]") {
  SeqEntry t1, t2;
  LevenshteinDistance compare;
  compare.setIdentity(0.05f);

  SECTION("Compare two equal strings") {
    t1.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
    t2.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");

    REQUIRE(compare.Compare(t1, t2) == true);
  }

  SECTION("Compare two very different strings") {
    t1.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
    t2.set_seq("ggatcctcatagcggctattgcgaaaagctatttcgcggccctagcga");

    REQUIRE(compare.Compare(t1, t2) == false);
  }

  SECTION("compare two similar strings of differing length") {
    t1.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
    t2.set_seq("acgtagcgcggctatagcgcataaatcctctagcgctatcttcgggttagca");

    REQUIRE(compare.Compare(t1, t2));
  }

  SECTION("compare two similar strings of same length") {
    t1.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
    t2.set_seq("acgtagcgcggctatagcgcataaatgggtctagcgctatcttcgggttagca");

    REQUIRE(compare.Compare(t1, t2));
  }
}

void empty_test(float identity) {
  SeqEntry t1, t2;
  LevenshteinDistance compare;

  SECTION("With identity " + std::to_string(identity)) {

    compare.setIdentity(identity);

    SECTION("First sequence is empty") {
      t1.set_seq("");
      t2.set_seq("a");

      REQUIRE(!compare.Compare(t1, t2));
    }

    SECTION("Second Sequence is empty") {
      t1.set_seq("a");
      t2.set_seq("");

      REQUIRE(!compare.Compare(t1, t2));
    }
  }
}

TEST_CASE("Levenshtein properly handles empty sequences.\n"
          "Everything is 100%% different from an empty string",
          "[levenshtein]") {
  empty_test(0.05f);
  empty_test(1.00f);
  empty_test(0.00f);
}

void test_same_sequence(float identity) {
  SeqEntry seq;
  LevenshteinDistance compare;
  seq.set_seq("acgt");

  SECTION("when identity is " + std::to_string(identity)) {
    compare.setIdentity(identity);

    REQUIRE(compare.Compare(seq, seq));
  }
}

TEST_CASE("Levenshtein properly handles same sequence.\n"
          "Should always be compared true.",
          "[levenshtein]") {

  test_same_sequence(0.05f);
  test_same_sequence(0.00f);
  test_same_sequence(1.00f);
}
