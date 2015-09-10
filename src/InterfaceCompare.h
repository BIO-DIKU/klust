#ifndef SRC_INTERFACE_COMPARE_H
#define SRC_INTERFACE_COMPARE_H

#include "Sequence.h"

class InterfaceCompare {
    public:
        virtual bool compare(Sequence* seq1, Sequence* seq2) = 0;

        void setIdentity(float id) { m_identity = id; }
        float getIdentity() const { return m_identity; }

    protected:
        float m_identity; // Similarity identity
};

#endif // SRC_INTERFACE_COMPARE_H