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

#include <vector>
#include <memory>

#include "../interface_clust.h"
#include "../resulttypes/sequence_result.h"
#include "../resulttypes/cluster_result.h"
#include "naive_clust.h"

NaiveClust::NaiveClust() : m_cluster_number(0) {
  std::vector<ClusterResult> m_summations;
}

SequenceResult NaiveClust::addSequence(SeqEntry& seq) {
  SequenceResult r(&seq, m_cluster_number, SequenceResult::ResultType::kCentroid);
  m_summations.emplace_back(m_cluster_number);

  m_cluster_number++;

  return r;
}

std::vector<ClusterResult> NaiveClust::finish() {
  return m_summations;
}