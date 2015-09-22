/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

#include "sequence.h"

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

const std::string& Sequence::getSequence() const {
    return m_sequence;
}

std::string& Sequence::getSequence() {
    return m_sequence;
}

void Sequence::setSequence(const std::string& str) {
    m_sequence = str;
}

const std::string& Sequence::getComment() const {
    return m_comment;
}

std::string& Sequence::getComment() {
    return m_comment;
}

void Sequence::setComment(const std::string& str) {
    m_comment = str;
}

int Sequence::getLineNumber() const {
    return m_lineNumber;
}

void Sequence::setLineNumber(int lineNumber) {
    m_lineNumber = lineNumber;
}

const KmerType* Sequence::getKmer() const {
    return m_kmers;
}

KmerType* Sequence::getKmer() {
    return m_kmers;
}

int Sequence::getKmersNum() const {
    return m_kmersSize;
}