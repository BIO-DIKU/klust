#include "Sequence.h"

Sequence::Sequence(const std::string& sequence,
                   const std::string& comment,
                   int lineNumber) :
    m_sequence(sequence),
    m_comment(comment),
    m_lineNumber(lineNumber),
    m_kmers(nullptr),
    m_kmersSize(0)
{
}

Sequence::Sequence(const Sequence& other) :
    m_sequence(other.m_sequence),
    m_comment(other.m_comment),
    m_lineNumber(other.m_lineNumber)
{
    m_kmersSize = other.m_kmersSize;
    m_kmers = new KmerType[m_kmersSize];

    for(int i = 0; i < m_kmersSize; ++i) {
        m_kmers[i] = other.m_kmers[i];
    }
}

Sequence::Sequence(Sequence&& other) noexcept :
    m_sequence(std::move(other.m_sequence)),
    m_comment(std::move(other.m_comment)),
    m_lineNumber(std::move(other.m_lineNumber)),
    m_kmers(std::move(other.m_kmers)),
    m_kmersSize(std::move(other.m_kmersSize))
{
}

Sequence& Sequence::operator=(const Sequence& other) {
    if(this != &other) {
        m_sequence = other.m_sequence;
        m_comment = other.m_comment;
        m_lineNumber = other.m_lineNumber;
        m_kmersSize = other.m_kmersSize;
        m_kmers = new KmerType[m_kmersSize];

        for(int i = 0; i < m_kmersSize; ++i) {
            m_kmers[i] = other.m_kmers[i];
        }
    }
    return *this;
}

Sequence::~Sequence() {
    if(m_kmers) {
        delete[] m_kmers;
    }
}

bool Sequence::kmersGenerated() const {
    return m_kmers;
}