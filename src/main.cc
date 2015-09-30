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

#include "main_control.h"

static void PrintVersion() {
  std::cout << "This is the version.\n";
}

static void PrintHelp() {
  std::cout <<
  "Usage: klust [options] <file(s)>\n"
  "\n"
  "[options]:\n"
  "-i --id <float>                         Similarity identity\n"
  "                                        (default=0.9).\n"
  "-o --output <string>                    Output file\n"
  "                                        (default=stdout).\n"
  "-f --format <int>                       Output format (default=1):\n"
  "                                           1: Tabular.\n"
  "                                           2: Centroids in\n"
  "                                              FASTA/FASTQ format.\n"
  "                                           3: Clusters in\n"
  "                                              FASTA/FASTQ format.\n"
  "                                           4: Pairwise sequence\n"
  "                                              alignments in\n"
  "                                              FASTA/FASTQ format.\n"
  "                                           5: Pairwise sequence\n"
  "                                              alignments in\n"
  "                                              pretty printed format.\n"
  "                                           6: Multiple sequence\n"
  "                                              alignments in\n"
  "                                              FASTA/FASTQ format.\n"
  "                                           7: Multiple sequence\n"
  "                                              alignments\n"
  "                                              with consensus\n"
  "                                              in FASTA/FASTQ format.\n"
  "-p --protein                            Input sequences are protein.\n"
  "-c --complement                         Also search the reverse\n"
  "                                        complement strand.\n"
  "-C --comparison <string>                Comparison type\n"
  "                                        (default=kmer):\n"
  "                                           kmer:  fast kmer based\n"
  "                                                  comparison.\n"
  "                                           align: slow alignment\n"
  "                                                  based comparison.\n"
  "-k --kmer_size <int>                    K-mer size to use for\n"
  "                                        sequence comparison\n"
  "                                        (default=5).\n"
  "-s --sort_input <string>                Sort input sequences by:\n"
  "                                        dec: decreasing length.\n"
  "                                        inc: increasing length.\n"
  "-K --keep_names                         Use sequence names instead\n"
  "                                        of sequence indexes in\n"
  "                                        output.\n"
  "-E --score_encoding <Phred33|Phred64>   Specify FASTQ score encoding\n"
  "                                        (default=Phred33).\n"
  "-S --score_min <int>                    Minimum Phred score in\n"
  "                                        matches.\n"
  "-m --max_rejects <int>                  Max number of rejects when\n"
  "                                        searching for centroid.\n"
  "-t --threads <int>                      Threads to use (default=1).\n"
  "-q --quiet                              Print nothing to stderr\n"
  "                                        except fatal errors.\n"
  "-v --version                            Output program version.\n"
  "-V --verbose                            Enable verbose messages.\n"
  "\n"
  "Documentation: https://github.com/BIO-DIKU/klust";
}

static int AnalyzeInput(int argc, char *argv[]) {
  // CLI argument parsing
  static struct option long_options[] = {
    {"id",              required_argument,  0, 'i'},
    {"output",          required_argument,  0, 'o'},
    {"format",          required_argument,  0, 'f'},
    {"protein",         no_argument,        0, 'p'},
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
      case 'p':
        break;
      case 'c':
        break;
      case 'C':
        break;
      case 'k':
        break;
      case 's':
        break;
      case 'K':
        break;
      case 'E':
        break;
      case 'S':
        break;
      case 'm':
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
        PrintHelp();
        return EXIT_FAILURE;
    }
  }

  if (argc < optind + 1) {
    PrintHelp();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (int ret = AnalyzeInput(argc, argv))
    return ret;

  // MainControl::instance()->setKmergen(new NaiveKmergen());
  // MainControl::instance()->setCompare(new NaiveCompare());
  // MainControl::instance()->setClust(new NaiveClust());

  return MainControl::instance()->run();
}
