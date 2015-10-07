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

#include "kmer_comparison.h"

#include <algorithm>
#include <cmath>
#include <memory>

#include "kmer_collection.h"
#include "seq_entry.h"

double KmerComparison::Compare(const SeqEntry& seq1, const SeqEntry& seq2) {
  // length of input sequences
  size_t seq1_len = seq1.seq().length(),
         seq2_len = seq2.seq().length();

  // shared pointers to longest and shortest input sequences
  std::shared_ptr<SeqEntry> longer_seq = seq1_len >= seq2_len ? std::make_shared<SeqEntry>(seq1)
                                                              : std::make_shared<SeqEntry>(seq2);

  std::shared_ptr<SeqEntry> shorter_seq = seq1_len >= seq2_len ? std::make_shared<SeqEntry>(seq2)
                                                               : std::make_shared<SeqEntry>(seq1);

  // kmercollections for the two sequences
  KmerCollection shorter_kmers(shorter_seq, kmerSize_, stepSize_);
  KmerCollection longer_kmers(longer_seq, kmerSize_, stepSize_);

  // allocate array of length equal to the number of different kmers
  static const int kmer_count = std::pow(4, kmerSize_);
  int *kmers = new int[kmer_count]();  // zero initialized due to ()

  int cur_dist = 0;

  auto longer_it = longer_kmers.begin();
  auto shorter_it = shorter_kmers.begin();

  // count k-mers in shorter sequence and prefix of longer sequence, store the
  // difference between the number of occurring k-mers in a single "frequency
  // vector" and maintain the current Manhattan distance between the sequences
  while (shorter_it != shorter_kmers.end()) {
    kmers[*longer_it]++ < 0 ? --cur_dist : ++cur_dist;
    kmers[*shorter_it]-- > 0 ? --cur_dist : ++cur_dist;

    ++shorter_it;
    ++longer_it;
  }

  int min_dist = cur_dist;  // the least distance window so far

  // maximum possible distance in the window, when the sequences share no k-mers
  int total = 2 * (shorter_seq->seq().size() - kmerSize_ + 1);

  double similarity = 0;

  /*
   * actgactgactg
   * actgactgactgactgactg
   * ^^^^     ^^^^
   *  |        |
   *  |     longer_it point at k-mer moving into window
   * exiting_kmer_it points at k-mer moving out of window
   */
  for (auto exiting_kmer_it = longer_kmers.begin();
       longer_it != longer_kmers.end(); ++longer_it, ++exiting_kmer_it) {
    if (*exiting_kmer_it == *longer_it)
      continue;   // same kmers, so no need to calculate new distance

    // if changed for the better, decrement distance, otherwise increment
    kmers[*exiting_kmer_it]  > 0 ? --cur_dist : ++cur_dist;
    kmers[*longer_it] < 0 ? --cur_dist : ++cur_dist;

    // adjust k-mer count from change
    --kmers[*exiting_kmer_it];
    ++kmers[*longer_it];

    min_dist = std::min(cur_dist, min_dist);
  }

  similarity = (double) (total - min_dist) / (double) total;

  delete[] kmers;
  return similarity;
}
