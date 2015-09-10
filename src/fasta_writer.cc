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

#include <fstream>

#include "fasta_writer.h"

FastaWriter::FastaWriter() :
    m_writeFileStream(nullptr),
    m_writeStream(nullptr)
{
}

FastaWriter::~FastaWriter() {
    closeWriter();
}

int FastaWriter::openCoutWriter() {
    closeWriter();
    m_writeStream = &std::cout;
    return 0;
}

int FastaWriter::openFileWriter(const std::string& filename) {
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

void FastaWriter::closeWriter() {
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

int FastaWriter::write(const Sequence& seq) {
    if(m_writeStream) {
        *m_writeStream << seq.m_sequence;
        return 0;
    }
    return -1;
}
