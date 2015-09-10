#ifndef SRC_INTERFACE_KMERGEN_H
#define SRC_INTERFACE_KMERGEN_H

#include "Sequence.h"

class InterfaceKmergen {
    public:
        virtual void generateKmers(Sequence& seq) = 0;
};

#endif // SRC_INTERFACE_KMERGEN_H