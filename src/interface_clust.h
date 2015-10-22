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

#ifndef KLUST_INTERFACE_CLUST_H_
#define KLUST_INTERFACE_CLUST_H_

#include <vector>

#include "seq_entry.h"
#include "interface_compare.h"
#include "interface_kmergen.h"
#include "resulttypes/sequence_result.h"
#include "resulttypes/cluster_result.h"

class InterfaceClust {
 public:
  /**
   * Returns positive value if seq must be written to file
   */
  virtual SequenceResult addSequence(SeqEntry& seq) = 0;
  virtual std::vector<ClusterResult> finish() = 0;

  void setCompare(InterfaceCompare* compare) { m_compare = compare; }
  void setKmergen(InterfaceKmergen* kmergen) { m_kmergen = kmergen; }

 private:
  InterfaceCompare* m_compare;
  InterfaceKmergen* m_kmergen;
};

#endif // KLUST_INTERFACE_CLUST_H_
