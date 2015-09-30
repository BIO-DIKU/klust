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

#ifndef SRC_SEQUENCE_H
#define SRC_SEQUENCE_H

#include <string>

#include "defines.h"

class Sequence {
 public:
  Sequence(const std::string& sequence = "",
           const std::string& comment = "",
           int lineNumber = -1);
  Sequence(const Sequence& other);
  Sequence(Sequence&& other) noexcept;
  Sequence& operator=(const Sequence& other);

  virtual ~Sequence();

  bool kmersGenerated() const;

  const std::string& getSequence() const;
  std::string& getSequence();
  void setSequence(const std::string& str);

  const std::string& getComment() const;
  std::string& getComment();
  void setComment(const std::string& str);

  int getLineNumber() const;
  void setLineNumber(int lineNumber);

  const KmerType* getKmer() const;
  KmerType* getKmer();

  int getKmersNum() const;

 public:
  std::string m_sequence;
  std::string m_comment;
  int m_lineNumber;

  KmerType* m_kmers;
  int m_kmersSize;
};

#endif // SRC_SEQUENCE_H
