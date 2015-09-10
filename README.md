## Installation

### Compiling source

SeqScan compiles with C++11 support but has no dependencies on other external
libraries. To prepare makefiles for release versions of the library and
executable, download the source code (see above) and type:

$ tar -xzvf SeqScan-latest-src.tar.gz
$ cd SeqScan-latest-src
$ mkdir SeqScan-build
$ cd SeqScan-build
$ cmake ../SeqScan-latest-src

After running `make`, the static library will be in SeqScan-build/libseqscan.a
and the executable in SeqScan-build/seqscan. To install in the system folders
type `make install`.

To prepare makefiles for debugging, instead type:

$ mkdir SeqScan-debug
$ cd SeqScan-debug
$ cmake -DCMAKE_BUILD_TYPE=Debug ../SeqScan-latest-src
