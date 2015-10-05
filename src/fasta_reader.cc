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

#include "fasta_reader.h"

FastaReader::FastaReader() :
  m_reader(nullptr),
  m_readComment(""),
  m_nextLineNumber(0) {
}

FastaReader::~FastaReader() {
  closeReader();
}

int FastaReader::openReader(const std::string& filename) {
  closeReader();

  m_reader = new std::ifstream(filename);
  m_nextLineNumber = 1;

  if (!m_reader->is_open()) {
    closeReader();
    return -1;
  }

  return 0;
}

void FastaReader::closeReader() {
  if (m_reader) {
    if (m_reader->is_open()) {
      m_reader->close();
    }
    delete m_reader;
  }
  m_reader = nullptr;
  m_readComment = "";
  m_nextLineNumber = 0;
}

int FastaReader::getNextLine(SeqEntry& seq) {
  if (m_reader == nullptr) {
    return -2;
  }

  if (m_readComment.size() > 0) {
    seq.set_name(m_readComment);
  } else {
    seq.set_name("");
  }

  /* FIXME
  seq.m_sequence = "";
  seq.m_lineNumber = 0;

  while (std::getline(*m_reader, m_readComment)) {
    if (m_readComment[0] != '>') {
      seq.m_sequence += m_readComment;
      if (seq.m_lineNumber == 0) {
        seq.m_lineNumber = m_nextLineNumber;
      }
      m_nextLineNumber += 1;
    } else if (seq.m_sequence == "") {
      seq.m_comment = std::string(m_readComment, 1);
    } else {
      return 0;
    }
  }*/

  return -1;
}
