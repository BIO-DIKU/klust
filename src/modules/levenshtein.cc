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

#include "levenshtein.h"

#include <cctype>
#include <memory>

#include <BioIO/seq_entry.h>

#include "../utils.h"

bool LevenshteinDistance::compare(SeqEntry* seq1, SeqEntry* seq2) {
  const std::string& str1 = seq1->seq();
  const std::string& str2 = seq2->seq();

  // degenerate cases
  // Return true if the two strings are the same
  if (&str1 == &str2) return true;
  // If any of the string are empty they are always 100% different. Return false
  if (str1.empty() || str2.empty()) return false;

  // Get data for calculating relative distance.
  size_t lengthDiff = (str1.length() < str2.length()
        ? str2.length() - str1.length()
        : str1.length() - str2.length());
  size_t smallestLength = (str1.length() < str2.length()
        ? str1.length()
        : str2.length());
        
  // Maximal errors before fail-fast kicks in
  float maxErrors = getIdentity() * smallestLength + lengthDiff;

  // create two work arrays of integer distances
  std::unique_ptr<size_t[]> v0(new size_t[str2.length() + 1]);
  std::unique_ptr<size_t[]> v1(new size_t[str2.length() + 1]);

  // initialize v0 (the previous row of distances)
  // this row is A[0][i]: edit distance for an empty str1
  // the distance is just the number of characters to delete from str2
  for (size_t i = 0; i < str2.length() + 1; i++) {
    v0[i] = i;
  }

  for (size_t i = 0; i < str1.length(); i++) {
    // calculate v1 (current row distances) from the previous row v0

    // first element of v1 is A[i+1][0]
    //   edit distance is delete (i+1) chars from s to match empty t
    v1[0] = i + 1;
    size_t minErrors = v1[0];

    // use formula to fill in the rest of the row
    for (size_t j = 0; j < str2.length(); j++) {
      int cost = (tolower(str1[i]) == tolower(str2[j])) ? 0 : 1;
      v1[j + 1] = min3(v1[j] + 1, v0[j + 1] + 1, v0[j] + cost);
      if (v1[j + 1] < minErrors)
        minErrors = v1[j + 1];
    }

    if (minErrors > maxErrors) {
      // Fail Fast
      return false;
    }

    // Swap pointer v0 and v1
    v0.swap(v1);
  }

  size_t result = v0[str2.length()];

  float similarity = static_cast<float>((result - lengthDiff)) / smallestLength;
  return similarity < getIdentity();
}
