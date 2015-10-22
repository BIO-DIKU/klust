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
#include "../../src/interface_clust.h"
#include "../../src/resulttypes/sequence_result.cc"
#include "../../src/resulttypes/cluster_result.cc"
#include "../../src/seq_entry.h"


TEST_CASE("Cluster output should be correct according to input", "[naive_clust") {
  SeqEntry seq("test", "gattaca", {}, SeqEntry::SeqType::nucleotide);
  SeqEntry seq2("test2", "acattag", {}, SeqEntry::SeqType::nucleotide);

  NaiveClust clust;

  SequenceResult r = clust.addSequence(seq);
  SequenceResult r2 = clust.addSequence(seq2);

  SECTION("Naive clust should always result in Centroid") {
    REQUIRE( r.getType() == SequenceResult::ResultType::kCentroid );
    REQUIRE( r2.getType() == SequenceResult::ResultType::kCentroid );
  }

  SECTION("resulting clusters correspond to added sequences") {
    REQUIRE( r.getSequence() == &seq );
    REQUIRE( r2.getSequence() == &seq2);
  }

  SECTION("resulting clusters are in the same order as the order they were added") {
    REQUIRE( r.getClusterNumber() == 0 );
    REQUIRE( r2.getClusterNumber() == 1 );
  }

  SECTION("Cluster result are two clusters, both of size 1") {
    auto summations = clust.finish();
    REQUIRE( summations[0].getSequenceCount() == 1 );
    REQUIRE( summations[1].getSequenceCount() == 1 );
  }



}
