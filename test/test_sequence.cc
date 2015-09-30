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

#include <catch.hpp>

#include "../src/sequence.cc"

TEST_CASE("sequence can be constructed, copied and moved", "[sequence]") {

  Sequence t1;
  Sequence t2 = Sequence("Test 1", "Comment 1", 42);

  REQUIRE(t1.m_sequence == "");
  REQUIRE(t1.m_comment == "");
  REQUIRE(t1.m_lineNumber == -1);
  REQUIRE(t1.m_kmers == nullptr);
  REQUIRE(t1.m_kmersSize == 0);

  REQUIRE(t2.m_sequence == "Test 1");
  REQUIRE(t2.m_comment == "Comment 1");
  REQUIRE(t2.m_lineNumber == 42);

  REQUIRE(t2.kmersGenerated() == false);

  SECTION("Copy Sequence 2 to Sequence 1") {
    t1 = t2;

    REQUIRE(t1.m_sequence == "Test 1");
    REQUIRE(t1.m_comment == "Comment 1");
    REQUIRE(t1.m_lineNumber == 42);
  }
  SECTION("Use copy contructor for new Sequence") {
    Sequence t3(t2);

    REQUIRE(t3.m_sequence == "Test 1");
    REQUIRE(t3.m_comment == "Comment 1");
    REQUIRE(t3.m_lineNumber == 42);
  }
  SECTION("Use move contructor for new Sequence") {
    Sequence t4 = std::move(t2);

    REQUIRE(t4.m_sequence == "Test 1");
    REQUIRE(t4.m_comment == "Comment 1");
    REQUIRE(t4.m_lineNumber == 42);

    REQUIRE(t2.m_sequence == "");
    REQUIRE(t2.m_comment == "");
    REQUIRE(t2.m_lineNumber == 42);
  }
}
