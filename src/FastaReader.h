#ifndef SRC_FASTA_READER_H
#define SRC_FASTA_READER_H

#include <fstream>
#include <string>

#include "Sequence.h"

class FasteReader {
    public:
        FasteReader(const FasteReader&) = delete;
        FasteReader& operator=(const FasteReader&) = delete;

        FasteReader();
        virtual ~FasteReader();

        int openReader(const std::string& filename);
        void closeReader();

        int getNextLine(Sequence& seq);

    private:
        std::ifstream* m_reader;
        std::string m_readComment;
        int m_nextLineNumber;
};

#endif // SRC_FASTA_READER_H