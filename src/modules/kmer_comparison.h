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

#include <BioIO/seq_entry.h>

#include "../interface_compare.h"

class KmerComparison : public InterfaceCompare {
 public:
  KmerComparison(int kmer_size, int step_size)
      : kmer_size_(kmer_size),
        step_size_(step_size) {
  }

  /*
   * Returns true if the similarity of the two given SeqEntries is at
   * least the threshold similarity. Otherwise it returns false.
   */
  bool Compare(const SeqEntry& seq1, const SeqEntry& seq2);

  /*
   * Returns the similarity of the two given SeqEntries, i.e. a value in the
   * interval [0,1], where 0 means low similarity and 1 means high similarity.
   */
  double Similarity(const SeqEntry& seq1, const SeqEntry& seq2);

 private:
  int kmer_size_;
  int step_size_;
};

#endif  // KLUST_KMER_COMPARISON_H_
