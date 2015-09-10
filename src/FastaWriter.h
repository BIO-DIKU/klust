#ifndef SRC_FASTA_WRITER_H
#define SRC_FASTA_WRITER_H

#include <iostream>
#include <string>

#include "Sequence.h"

class FasteWriter {
    public:
        FasteWriter(const FasteWriter&) = delete;
        FasteWriter& operator=(const FasteWriter&) = delete;

        FasteWriter();
        virtual ~FasteWriter();

        int openCoutWriter();
        int openFileWriter(const std::string& filename);

        void closeWriter();

        int write(const Sequence& seq); // TODO

    private:
        std::ofstream* m_writeFileStream;
        std::ostream* m_writeStream;
};

#endif // SRC_FASTA_WRITER_H