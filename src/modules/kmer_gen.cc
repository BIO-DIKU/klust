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

#include "kmer_gen.h"

#include <string>

void KmerGen::generateKmers(Sequence& seq) {
  std::string& str = seq.m_sequence;
  const char* ptr = str.data();
  unsigned int kmerNum = str.size() - getK();

  if(seq.m_kmers) {
    delete[] seq.m_kmers;
  }
  seq.m_kmers = new KmerType[kmerNum];

  for(unsigned int i; i < kmerNum; ++i) {
    seq.m_kmers[i] = ((const KmerType*)ptr)[i];
  }
}