#ifndef SRC_FASTA_WRITER_H
#define SRC_FASTA_WRITER_H

#include <iostream>
#include <string>

#include "Sequence.h"

class FastaWriter {
    public:
        FastaWriter(const FastaWriter&) = delete;
        FastaWriter& operator=(const FastaWriter&) = delete;

        FastaWriter();
        virtual ~FastaWriter();

        int openCoutWriter();
        int openFileWriter(const std::string& filename);

        void closeWriter();

        int write(const Sequence& seq); // TODO

    private:
        std::ofstream* m_writeFileStream;
        std::ostream* m_writeStream;
};

#endif // SRC_FASTA_WRITER_H
