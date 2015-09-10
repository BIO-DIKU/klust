#ifndef SRC_MODULES_NAIVE_CLUST_H
#define SRC_MODULES_NAIVE_CLUST_H

#include "../InterfaceClust.h"

class NaiveClust : public InterfaceClust {
    public:
        int addSequence(Sequence& seq);
};

#endif // SRC_MODULES_NAIVE_CLUST_H