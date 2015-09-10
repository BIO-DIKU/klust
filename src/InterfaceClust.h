#ifndef SRC_INTERFACE_CLUST_H
#define SRC_INTERFACE_CLUST_H

#include "Sequence.h"
#include "InterfaceCompare.h"
#include "InterfaceKmergen.h"

class InterfaceClust {
    public:
        /**
        * Returns positive value if seq must be written to file
        */
        virtual int addSequence(Sequence& seq) = 0;

        void setCompare(InterfaceCompare* compare) { m_compare = compare; }
        void setKmergen(InterfaceKmergen* kmergen) { m_kmergen = kmergen; }

    private:
        InterfaceCompare* m_compare;
        InterfaceKmergen* m_kmergen;
};

#endif // SRC_INTERFACE_CLUST_H