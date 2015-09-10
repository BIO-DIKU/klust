#include "FastaReader.h"

FasteReader::FasteReader() :
    m_reader(nullptr),
    m_readComment(""),
    m_nextLineNumber(0)
{
}

FasteReader::~FasteReader() {
    closeReader();
}

int FasteReader::openReader(const std::string& filename) {
    closeReader();

    m_reader = new std::ifstream(filename);
    m_nextLineNumber = 1;

    if(!m_reader->is_open()) {
        closeReader();
        return -1;
    }

    return 0;
}

void FasteReader::closeReader() {
    if(m_reader) {
        if(m_reader->is_open()) {
            m_reader->close();
        }
        delete m_reader;
    }
    m_reader = nullptr;
    m_readComment = "";
    m_nextLineNumber = 0;
}

int FasteReader::getNextLine(Sequence& seq) {
    if(m_reader == nullptr) {
        return -2;
    }

    if(m_readComment.size() > 0) {
        seq.m_comment = std::string(m_readComment, 1);
    } else {
        seq.m_comment = "";
    }

    seq.m_sequence = "";
    seq.m_lineNumber = 0;

    while(std::getline(*m_reader, m_readComment))
    {
        if(m_readComment[0] != '>') {
            seq.m_sequence += m_readComment;
            if(seq.m_lineNumber == 0) {
                seq.m_lineNumber = m_nextLineNumber;
            }
            m_nextLineNumber += 1;
        }
        else if(seq.m_sequence == "") {
            seq.m_comment = std::string(m_readComment, 1);
        }
        else {
            return 0;
        }
    }

    return -1;
}