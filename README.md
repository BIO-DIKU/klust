# klust

## Synopsis

klust is a fast and memory efficient sequence clustering program for nucleotide and protein sequences.

```
Usage: klust [options] <file(s)>

[options]:
-i --id <float>                         Similarity identity 
                                        (default=0.9).
-o --output <string>                    Output file 
                                        (default=stdout).
-f --format <int>                       Output format (default=1):
                                           1: Tabular.
                                           2: Centroids in 
                                              FASTA/FASTQ format.
                                           3: Clusters in 
                                              FASTA/FASTQ format.
                                           4: Pairwise sequence 
                                              alignments in           
                                              FASTA/FASTQ format.
                                           5: Pairwise sequence 
                                              alignments in 
                                              pretty printed format.
                                           6: Multiple sequence 
                                              alignments in 
                                              FASTA/FASTQ format.
                                           7: Multiple sequence 
                                              alignments
                                              with consensus  
                                              in FASTA/FASTQ format.
-p --protein                            Input sequences are protein.
-c --complement                         Also search the reverse 
                                        complement strand.
-C --comparison <string>                Comparison type 
                                        (default=kmer):
                                           kmer:  fast kmer based 
                                                  comparison.
                                           align: slow alignment 
                                                  based comparison.
-k --kmer_size <int>                    K-mer size to use for               
                                        sequence comparison 
                                        (default=5).
-s --sort_input <string>                Sort input sequences by:
                                           dec: decreasing length.
                                           inc: increasing length.
-K --keep_names                         Use sequence names instead 
                                        of sequence indexes in 
                                        output.
-E --score_encoding <Phred33|Phred64>   Specify FASTQ score encoding
                                        (default=Phred33).
-S --score_min <int>                    Minimum Phred score in 
                                        matches.
-m --max_rejects <int>                  Max number of rejects when 
                                        searching for centroid.
-t --threads <int>                      Threads to use (default=1).
-q --quiet                              Print nothing to stderr 
                                        except fatal errors.
-v --version                            Output program version.
-V --verbose                            Enable verbose messages.

Documentation: https://github.com/BIO-DIKU/klust
```
## Download

## Installation

### Compiling source

Klust compiles with C++11 support but has no dependencies on other external
libraries. To get the source and make the project binary type the following:

```
$ git clone https://github.com/BIO-DIKU/klust.git
$ cd klust
$ cmake .
$ make
```

After running `make`, the executable will be in the root directory named BIO-DIKU-klust.

## About
The klust sequence clustering program utilizes a greedy clustering approach like USEARCH and CD-HIT bleh-blah. Klust is ideal for clustering of sequences in the size range xx-xxx such as 16S ribosomal RNA.

Sequence comparisons in klust are performed using either a k-mer or an alignment based algorithm which can be selected using the `--comparison` option.

The k-mer comparisons are based on the co-occurrence of oligos or k-mers in two sequences in order to determine the _Manhattan distance_ which is used as a metric for clustering. To alleviate the difference in sequence lengths between the compared sequences, a sliding window the size of the shortest sequences is used and the minimum Manhattan distance is chosen.   

The alignment comparisons are based on pairwise alignments between sequences and using the identity as a metric for clustering. The pairwise alignments are computed using an algorithm that locates all maximal exact matches between two sequences spanning a search space followed by the filtering of the matches according to sequence length, distance to search space corners and diagonal. Accepted matches are included in the alignment and the algorithm recurses into new inter-match search spaces until no more matches can be found.

Something about the clustering algorithm (what are clusters, centroids and cluster members).

The clustering algorithm assigns each sequence to exactly one cluster and each cluster is represented by a single centroid sequence. A cluster is a collection of sequences that have a close resemblance to each other, based on the given method of comparison and identity threshold. The centroid sequence is the sequence upon which this decision of assignment based on resemblance is based. The clustering algorithm seeks to minimize the number of resulting clusters, however the result is not guaranteed to be optimal.

The clustering algorithm works by processing the sequences in an online fashion and for each sequence, it is decided whether it is assigned to an existing cluster or it becomes the centroid of a new cluster. The centroids are stored in a doubly-linked list and processed in sequence. A sequence is compared to a centroid if the following criterion holds:

The number of distinct k-mers that the two sequences share is at least the number of distinct k-mers in the centroid times the identity threshold.

When a comparison is successful, the sequence is assigned to the cluster represented by that centroid and the centroid is moved to the front of the list. A given maximum number of comparisons (--max_rejects) are performed before creating a new cluster and prepending the centroid to the list.

## Input
Input data are files containing either FASTA or FASTQ formatted sequences. Files may be compressed with gzip or bzip2. The default quality score encoding for FASTQ format is Phred33, but may be changed using the `--score_encoding` option. If sequences are in FASTQ format the quality scores will be utilized such that any k-mer containing a residue with a quality score below the threshold specified with the `--score_min` option will be skipped if this option is used. Thus residues with a suboptimal quality score will have a reduced impact on the clustering.

## Output
Output from klust is written to stdout per default, but can be saved to file using the `--output` option.

### Tabular output
The default output format, which can be changed with the `--format` option, is a tab separated table where the first column is cluster number, the second column is the sequence index of the cluster centroid and subsequent columns are cluster member sequence indexes followed by a colon and the percent identity between the centroid and that particular cluster member.

It is possible in all types of output to replace the sequence index with the original sequence name by using the `--keep_names` option.

### FASTA/FASTQ output
Using `--format 2` the centroid sequences are output in FASTA or FASTQ format depending on the input format. The sequence names consist of the cluster number, centroid sequence index, cluster size, minimum, maximum and mean identity separated by spaces.

Using `--format 3` the entire clusters are output in FASTA or FASTQ format depending on the input format. The names of the centroid sequences are the same as with `--format 2`, but the cluster member sequence names consists of the cluster number, sequence index, and the identity relative to the centroid separated by spaces.

### Alignment output
Using `--format 4` pairwise alignments are output in FASTA or FASTQ format depending on the input format. The pairwise alignment consists of the controid sequence aligned with each of the cluster members. 

Using `--format 5` outputs pairwise alignments in a pretty printed format where matching residues are indicated by `|`.

Using `--format 6` multiple alignments are output in FASTA or FASTQ format depending on the input format.

Using `--format 7` does the same as `--format 6` but an additional consensus sequence is output for each cluster. The consensus sequence contains for each column in the alignment the most common residue or a gap if gaps are predominant:

    Sequence1   ATaCA-CGAGTAGCT
    Sequence2   ATGCA-CGAGTAGCT
    Sequence3   ATGCATCGAcTAG-T
    Consensus   ATGCA-CGAGTAGCT

If the input is FASTQ format the consensus sequence quality scores for each column will be the mean of the scores for that particular column.

The sequence naming scheme for the centroid and cluster member sequences are the same as with `--format 3`.

## Sequence identity
Sequence identity are either calculated as k-mer identity or alignment identity depending on the comparison method used (via the `--comparison` option).

K-mer identity is calculated bleh blah.

Alignment identity is calculated as the sum of matching residues over the length of the shortest sequence.

Kmer and alignment identity are not directly comparable. A k-mer identity of 85% may correspond to an alignment identity of 97%.

## Examples
For the following examples consider the following FASTA entries in the file `test.fna` (note that they are pre-sorted by decreasing sequence length):

```
>test1
GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
>test2
GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA
>test3
GGGACCGTCGACTACTACGCATCTTTACTTTATATATTTT
>test4
GGGACCGTCGACTACTACGCATCTTTACTTTATATATATT
>test5
GGCATCGACACATATCAGATCTATCAGCTGACTAGCATGA
>test6
GGGACCATCGACTACTACGCATCTTTACTTTATATATTTT
>test7
GGCATCGACACAATCACATCTATCAGCTGACTAGCATGA
```

### Tabular output
To cluster our example file and produce a table output to stdout do:

    $ klust --identity 0.8 test.fna

    0   0   2:95.1   3:92.7   5:97.6
    1   1   4:97.5   6:97.5

Using the `--keep_names` option replaces the sequence indexes with the original sequence names:

    $ klust --identity 0.8 --keep_names test.fna

    0   test1   test3:95.1   test4:92.7   test6:97.6
    1   test2   test5:97.5   test7:97.5

To save the output to a file instead of outputting to stdout use the `--output` option:

    $ klust --identity 0.8 --keep_names --output output.tab test.fna

To also search the reverse complement sequence use the `--complement` options:

$ klust --identity 0.8 --complement --output output.tab test.fna

### Sequence output

To output the centroid sequences use the `--format 2` option:

    $ klust --identity 0.8 --format 2 test.fna 

    >0 0 3 92.7 97.6 95.1
    GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
    >1 1 2 97.5 97.5 97.5
    GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA

Again, the `--keep_names` option replace the sequence index with the original sequence name:

    $ klust --identity 0.8 --keep_names --format 2 test.fna 

    >0 test1 3 92.7 97.6 95.1
    GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
    >1 test2 2 97.5 97.5 97.5
    GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA

To output the clustered sequences use the `--format 3` option:

    $ klust --identity 0.8 --format 3 test.fna
    >0 0 3 92.7 97.6 95.1
    GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
    >0 2 95.1
    GGGACCGTCGACTACTACGCATCTTTACTTTATATATTTT
    >0 3 92.7
    GGGACCGTCGACTACTACGCATCTTTACTTTATATATATT
    >0 5 97.6
    GGGACCATCGACTACTACGCATCTTTACTTTATATATTTT
    >1 1 2 97.5 97.5 97.5
    GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA
    >1 4 97.5
    GGCATCGACACATATCAGATCTATCAGCTGACTAGCATGA
    >1 6 97.5
    GGCATCGACACAATCACATCTATCAGCTGACTAGCATGA

### Alignment output
To produce pairwise alignment output use the `--format 4` option:

    $ klust --identity 0.8 --format 4 test.fna
    
    >0 0 3 92.7 97.6 95.1
    GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
    >0 2 95.1
    GGGACCGTCGAC-TACTACGCATCTTTACTTTATATATTTT
    >0 0 3 92.7 97.6 95.1
    GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
    >0 3 92.7
    GGGACCGTCGAC-TACTACGCATCTTTACTTTATATATATT
    >0 0 3 92.7 97.6 95.1
    GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
    >0 5 97.6
    GGGACCATCGAC-TACTACGCATCTTTACTTTATATATTTT
    >1 1 2 97.5 97.5 97.5
    GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA
    >1 4 97.5
    GGCATCGACACATATCAGATCTATCAGCTGACTAGCATGA
    >1 1 2 97.5 97.5 97.5
    GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA
    >1 6 97.5
    GGCATCGACACA-ATCACATCTATCAGCTGACTAGCATGA

Using the `--format 5` option will output pairwise alignments in a pretty printed format:

    $ klust --identity 0.8 --format 4 test.fna
    
    0 0 3 92.7 97.6 95.1 GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
                         |||||| ||||| ||||||||||||||||||||||||||||
    0 2 95.1             GGGACCGTCGAC-TACTACGCATCTTTACTTTATATATTTT

    0 0 3 92.7 97.6 95.1 GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
                         |||||| ||||| ||||||||||||||||||||||||| ||
    0 3 92.7             GGGACCGTCGAC-TACTACGCATCTTTACTTTATATATATT

    0 0 3 92.7 97.6 95.1 GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
                         |||||||||||| ||||||||||||||||||||||||||||
    0 5 97.6             GGGACCATCGAC-TACTACGCATCTTTACTTTATATATTTT

    1 1 2 97.5 97.5 97.5 GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA
                         ||||||||||||||||| ||||||||||||||||||||||
    1 4 97.5             GGCATCGACACATATCAGATCTATCAGCTGACTAGCATGA

    1 1 2 97.5 97.5 97.5 GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA
                         |||||||||||| |||||||||||||||||||||||||||
    1 6 97.5             GGCATCGACACA-ATCACATCTATCAGCTGACTAGCATGA

To produce multiple alignment output use the `--format 6` option:

 $ klust --identity 0.8 --format 5 test.fna
    
    >0 0 3 92.7 97.6 95.1
    GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
    >0 2 95.1
    GGGACCGTCGAC-TACTACGCATCTTTACTTTATATATTTT
    >0 3 92.7
    GGGACCGTCGAC-TACTACGCATCTTTACTTTATATATATT
    >0 5 97.6
    GGGACCATCGAC-TACTACGCATCTTTACTTTATATATTTT
    >1 1 2 97.5 97.5 97.5
    GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA
    >1 4 97.5
    GGCATCGACACATATCAGATCTATCAGCTGACTAGCATGA
    >1 6 97.5
    GGCATCGACACA-ATCACATCTATCAGCTGACTAGCATGA

Using the `--format 6` option will add a consensus sequence for each cluster:

 $ klust --identity 0.8 --format 5 test.fna
    
    >0 0 3 92.7 97.6 95.1
    GGGACCATCGACCTACTACGCATCTTTACTTTATATATTTT
    >0 2 95.1
    GGGACCGTCGAC-TACTACGCATCTTTACTTTATATATTTT
    >0 3 92.7
    GGGACCGTCGAC-TACTACGCATCTTTACTTTATATATATT
    >0 5 97.6
    GGGACCATCGAC-TACTACGCATCTTTACTTTATATATTTT
    >0 Consensus
    GGGACCATCGA-CTACTACGCATCTTTACTTTATATATTTT
    >1 1 2 97.5 97.5 97.5
    GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA
    >1 4 97.5
    GGCATCGACACATATCAGATCTATCAGCTGACTAGCATGA
    >1 6 97.5
    GGCATCGACACA-ATCACATCTATCAGCTGACTAGCATGA
    >1 Consensus
    GGCATCGACACATATCACATCTATCAGCTGACTAGCATGA    

## Copyright
Copyright © 2015 BIO-DIKU - All rights reserved.

## License
GNU General Public License version 2

http://www.gnu.org/copyleft/gpl.html

## Disclaimer
All generic disclaimers apply.

## Contact
https://github.com/BIO-DIKU/klust

## Cite
Manuscript is in preparation. Until published, please cite:

https://github.com/BIO-DIKU/klust

## Bugs
Please report bugs:

https://github.com/BIO-DIKU/klust/issues
