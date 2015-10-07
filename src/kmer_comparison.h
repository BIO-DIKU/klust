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

#ifndef KLUST_KMER_COMPARISON_H_
#define KLUST_KMER_COMPARISON_H_

#include "seq_entry.h"

class KmerComparison {
 public:
  KmerComparison(int kmerSize, double threshold, int stepSize)
      : kmerSize_(kmerSize),
        threshold_(threshold),
        stepSize_(stepSize) {
  }

  /*
   * Returns the similarity of the two given SeqEntry's, i.e. a value in the
   * interval [0,1], where 0 means low similarity and 1 means high similarity.
   */
  double Compare(const SeqEntry& seq1, const SeqEntry& seq2);

 private:
  int kmerSize_;
  double threshold_;
  int stepSize_;
};

#endif  // KLUST_KMER_COMPARISON_H_
