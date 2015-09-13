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

#include <getopt.h>
#include <iostream>
#include <string>

#include "defines.h"
#include "main_control.h"
#include "modules/naive_clust.h"

static void PrintVersion() {
  std::cout << "This is the version.\n";
}

static void PrintHelp(char *argv[]) {
  std::cout << "Usage: " << argv[0] << " [options] <file(s)>\n";
}

static int AnalyzeInput(int argc, char *argv[]) {
  // CLI argument parsing
  static struct option long_options[] = {
    {"id",              required_argument,  0, 'i'},
    {"output",          required_argument,  0, 'o'},
    {"format",          required_argument,  0, 'f'},
    {"complement",      no_argument,        0, 'c'},
    {"comparison",      required_argument,  0, 'C'},
    {"kmer_size",       required_argument,  0, 'k'},
    {"sort_input",      required_argument,  0, 's'},
    {"keep_names",      no_argument,        0, 'K'},
    {"score_encoding",  required_argument,  0, 'E'},
    {"score_min",       required_argument,  0, 'S'},
    {"max_rejects",     required_argument,  0, 'm'},
    {"threads",         required_argument,  0, 't'},
    {"quiet",           no_argument,        0, 'q'},
    {"version",         no_argument,        0, 'v'},
    {"verbose",         no_argument,        0, 'V'},
    {0,                 0,                  0,  0 }
  };

  int opt, option_index = 0;
  while ((opt = getopt_long(argc, argv, "i:o:f:cC:k:s:KE:S:m:t:qvV",
          long_options, &option_index)) != -1) {
    switch (opt) {
      case 'i':
        MainControl::instance()->setIdentity(atof(optarg));
        break;
      case 'o':
        break;
      case 'f':
        break;
      case 't':
        break;
      case 'q':
        break;
      case 'v':
        PrintVersion();
        break;
      case 'V':
        break;
      default:
        std::cout << "unexpected argument" << std::endl;
        PrintHelp(argv);
        return 1;
    }
  }

  if (argc < optind + 1) {
    PrintHelp(argv);
    return 1;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  if (int ret = AnalyzeInput(argc, argv))
    return ret;

  // MainControl::instance()->setKmergen(new NaiveKmergen());
  // MainControl::instance()->setCompare(new NaiveCompare());
  // MainControl::instance()->setClust(new NaiveClust());

  return MainControl::instance()->run();
}
