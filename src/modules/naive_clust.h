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

#ifndef KLUST_MODULES_NAIVE_CLUST_H_
#define KLUST_MODULES_NAIVE_CLUST_H_

#include <vector>
#include <memory>

#include "../interface_clust.h"
#include "../seq_entry.h"

struct Centroid {
  SeqEntry* seq;
  uint32_t count = 1;
  uint32_t clusterNumber;

  Centroid(SeqEntry* seq, uint32_t clusterNumber) {
    this->seq = seq;
    this->clusterNumber = clusterNumber;
  }
};

/**
 * Extremely simple clustering, which puts every sequence in its own cluster.
 */
class NaiveClust : public InterfaceClust {
 public:
  NaiveClust();

  int addSequence(SeqEntry& seq);

  /**
   * Return a shared pointer to the vector of clusters.
   *
   * @return  Vector of generated clusters.
   */
  std::shared_ptr<std::vector<Centroid>> getClusters();
 private:
  uint32_t m_cluster_count;
  std::shared_ptr<std::vector<Centroid>> m_clusters;
};

#endif // KLUST_MODULES_NAIVE_CLUST_H_
