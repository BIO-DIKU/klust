#ifndef SRC_FASTA_READER_H
#define SRC_FASTA_READER_H

#include <fstream>
#include <string>

#include "Sequence.h"

class FastaReader {
    public:
        FastaReader(const FastaReader&) = delete;
        FastaReader& operator=(const FastaReader&) = delete;

        FastaReader();
        virtual ~FastaReader();

        int openReader(const std::string& filename);
        void closeReader();

        int getNextLine(Sequence& seq);

    private:
        std::ifstream* m_reader;
        std::string m_readComment;
        int m_nextLineNumber;
};

#endif // SRC_FASTA_READER_H
