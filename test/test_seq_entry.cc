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

#include "catch.hpp"

#include "../src/seq_entry.cc"

TEST_CASE("sequences can be constructed, copied and moved", "[sequence]") {
  SeqEntry t1;
  SeqEntry t2 = SeqEntry("Name", "Sequence", {}, SeqEntry::SeqType::protein);

  REQUIRE(t1.name() == "");
  REQUIRE(t1.seq() == "");
  REQUIRE(t1.scores().empty());
  REQUIRE(t1.type() == SeqEntry::SeqType::nucleotide);

  REQUIRE(t2.name() == "Name");
  REQUIRE(t2.seq() == "Sequence");
  REQUIRE(t2.scores().empty());
  REQUIRE(t2.type() == SeqEntry::SeqType::protein);

  SECTION("Copy SeqEntry 2 to SeqEntry 1") {
    t1 = t2;

    REQUIRE(t1.name() == "Name");
    REQUIRE(t1.seq() == "Sequence");
    REQUIRE(t1.scores().empty());
    REQUIRE(t1.type() == SeqEntry::SeqType::protein);
  }

  SECTION("Use copy contructor for new SeqEntry") {
    SeqEntry t3(t2);

    REQUIRE(t3.name() == "Name");
    REQUIRE(t3.seq() == "Sequence");
    REQUIRE(t3.scores().empty());
    REQUIRE(t3.type() == SeqEntry::SeqType::protein);
  }

  SECTION("Use move contructor for new SeqEntry") {
    SeqEntry t4 = std::move(t2);

    REQUIRE(t4.name() == "Name");
    REQUIRE(t4.seq() == "Sequence");
    REQUIRE(t4.scores().empty());
    REQUIRE(t4.type() == SeqEntry::SeqType::protein);

    REQUIRE(t2.name() == "");
    REQUIRE(t2.seq() == "");
    REQUIRE(t2.scores().empty());
    REQUIRE(t2.type() == SeqEntry::SeqType::protein);
  }
}

TEST_CASE("subsequences can be extracted from sequences", "[sequence]") {
  SeqEntry t1 = SeqEntry("Name", "Sequence", {}, SeqEntry::SeqType::nucleotide);

  REQUIRE(t1.name() == "Name");
  REQUIRE(t1.seq() == "Sequence");
  REQUIRE(t1.scores().empty());
  REQUIRE(t1.type() == SeqEntry::SeqType::nucleotide);

  SeqEntry t2 = t1.SubSeq(2, 4);

  // t1 stays unchanged
  REQUIRE(t1.name() == "Name");
  REQUIRE(t1.seq() == "Sequence");
  REQUIRE(t1.scores().empty());
  REQUIRE(t1.type() == SeqEntry::SeqType::nucleotide);

  // t2 contains expected subsequence of t1 and they are otherwise identical
  REQUIRE(t2.name() == "Name");
  REQUIRE(t2.seq() == "quen");
  REQUIRE(t2.scores().empty());
  REQUIRE(t2.type() == SeqEntry::SeqType::nucleotide);
}
