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

#include <memory>
#include <vector>

#include "../../src/modules/naive_clust.cc"
#include "../../src/seq_entry.h"

TEST_CASE("Add a sequence after getUnique has been called", "[naive_clust]") {
  SeqEntry seq("test", "gattaca", {}, SeqEntry::SeqType::nucleotide);
  SeqEntry seq2("test2", "acattag", {}, SeqEntry::SeqType::nucleotide);

  NaiveClust clust;

  REQUIRE( clust.addSequence(seq) == 0 );

  auto clusters = clust.getClusters();

  REQUIRE( clusters->size() == 1 );

  REQUIRE( clust.addSequence(seq2) == 0);

  REQUIRE( clusters->size() == 2 );
  REQUIRE( clust.getClusters() == clusters );
}

TEST_CASE("Cluster output should be correct according to input", "[naive_clust") {
  SeqEntry seq("test", "gattaca", {}, SeqEntry::SeqType::nucleotide);
  SeqEntry seq2("test2", "acattag", {}, SeqEntry::SeqType::nucleotide);

  NaiveClust clust;

  REQUIRE( clust.addSequence(seq) == 0 );
  REQUIRE( clust.addSequence(seq2) == 0 );

  auto clusters = clust.getClusters();

  SECTION("resulting clusters correspond to added sequences") {
    REQUIRE( (*clusters)[0].seq == &seq );
    REQUIRE( (*clusters)[1].seq == &seq2);
  }

  SECTION("resulting clusters are in the same order as the order they were added") {
    REQUIRE( (*clusters)[0].clusterNumber == 0 );
    REQUIRE( (*clusters)[1].clusterNumber == 1 );
  }

  SECTION("Naive clust should always only put a single sequence in every cluster") {
    REQUIRE( (*clusters)[0].count == 1 );
    REQUIRE( (*clusters)[1].count == 1 );
  }

}

