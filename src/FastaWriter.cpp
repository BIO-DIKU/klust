#include "FastaWriter.h"

#include <fstream>

FasteWriter::FasteWriter() :
    m_writeFileStream(nullptr),
    m_writeStream(nullptr)
{
}

FasteWriter::~FasteWriter() {
    closeWriter();
}

int FasteWriter::openCoutWriter() {
    closeWriter();
    m_writeStream = &std::cout;
    return 0;
}

int FasteWriter::openFileWriter(const std::string& filename) {
    closeWriter();

    m_writeFileStream = new std::ofstream();
    m_writeStream = m_writeFileStream;

    m_writeFileStream->open(filename, std::ofstream::out | std::ofstream::app);
    if(!m_writeFileStream->is_open()) {
        closeWriter();
        return -1;
    }
    return 0;
}

void FasteWriter::closeWriter() {
    if(m_writeFileStream) {
        m_writeFileStream->close();

        delete m_writeFileStream;

        m_writeFileStream = nullptr;
        m_writeStream = nullptr;
    }
    else if(m_writeStream) {
        m_writeStream = nullptr;
    }
}

int FasteWriter::write(const Sequence& seq) {
    if(m_writeStream) {
        *m_writeStream << seq.m_sequence;
        return 0;
    }
    return -1;
}