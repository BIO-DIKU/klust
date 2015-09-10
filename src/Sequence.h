#ifndef SRC_SEQUENCE_H
#define SRC_SEQUENCE_H

#include <string>

#include "Defines.h"

class Sequence {
    public:
        Sequence(const std::string& sequence = "",
                 const std::string& comment = "",
                 int lineNumber = -1);
        Sequence(const Sequence& other);
        Sequence(Sequence&& other) noexcept;
        Sequence& operator=(const Sequence& other);

        virtual ~Sequence();

        bool kmersGenerated() const;

    public:
        std::string m_sequence;
        std::string m_comment;
        int m_lineNumber;

        KmerType* m_kmers;
        int m_kmersSize;
};

#endif // SRC_SEQUENCE_H