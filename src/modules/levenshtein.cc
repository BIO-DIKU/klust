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

#include "../sequence.h"

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

bool LevenshteinDistance::compare(Sequence* seq1, Sequence* seq2) {
    std::string str1 = seq1->getSequence();
    std::string str2 = seq2->getSequence();

    // degenerate cases
    if (&str1 == &str2) return 0.0f;
    if (str1.length() == 0) return str2.length();
    if (str2.length() == 0) return str1.length();

    // create two work vectors of integer distances
    int* v0 = new int[str2.length() + 1];
    int* v1 = new int[str2.length() + 1];

    // Get data for calculating relative distance.
    int lengthDiff = (int) (str1.length() < str2.length()
                            ? str2.length() - str1.length()
                            : str1.length() - str2.length());
    int smallestLength = (int) (str1.length() < str2.length() ? str1.length() : str2.length());
    // Maximal errors before fail-fast kicks in
    float maxErrors = getIdentity() * smallestLength + lengthDiff;

    // initialize v0 (the previous row of distances)
    // this row is A[0][i]: edit distance for an empty str1
    // the distance is just the number of characters to delete from str2
    for (int i = 0; i < (int)str2.length() + 1; i++) {
        v0[i] = i;
    }

    for (int i = 0; i < (int)str1.length(); i++)
    {
        // calculate v1 (current row distances) from the previous row v0

        // first element of v1 is A[i+1][0]
        //   edit distance is delete (i+1) chars from s to match empty t
        v1[0] = i + 1;
        int minErrors = v1[0];
        
        // use formula to fill in the rest of the row
        for (int j = 0; j < (int)str2.length(); j++)
        {
            int cost = ((str1[i]|32) == (str2[j]|32)) ? 0 : 1;
            v1[j + 1] = MIN3(v1[j] + 1, v0[j + 1] + 1, v0[j] + cost);
            if (v1[j + 1] < minErrors)
                minErrors = v1[j + 1];
        }
       
        if (minErrors > maxErrors) {
            delete[] v0;
            delete[] v1;
            // Fail Fast
            return false;
        }

        // Swap pointer v0 and v1
        int* tmp = v0;
        v0 = v1;
        v1 = tmp;
    }

    int result = v0[str2.length()];

    delete[] v0;
    delete[] v1;

    return ((float)(result - lengthDiff) / smallestLength) < getIdentity();
}