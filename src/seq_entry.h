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

#ifndef KLUST_SEQ_ENTRY_H_
#define KLUST_SEQ_ENTRY_H_

#include <string>
#include <vector>

class SeqEntry {
 public:
  enum class SeqType {
    nucleotide,
    protein
  };

  SeqEntry();
  SeqEntry(const std::string& name, const std::string& sequence,
           const std::vector<uint8_t>& scores, SeqEntry::SeqType sequence_type);

  /*
   * Returns a SeqEntry containing the (consecutive) subsequence of the
   * SeqEntry object it is called on, starting at the given index and of
   * the given length.
   */
  SeqEntry SubSeq(size_t i, size_t len) const;

  // accessors
  const std::string& name() const { return name_; }
  const std::string& seq() const { return seq_; }
  const std::vector<uint8_t>& scores() const { return scores_; }
  SeqType type() const { return type_; }

  // mutators
  void set_name(const std::string& name) { name_ = name; }
  void set_seq(const std::string& sequence) { seq_ = sequence; }
  void set_scores(const std::vector<uint8_t>& scores) { scores_ = scores; }
  void set_type(SeqType type) { type_ = type; }

 private:
  std::string name_;
  std::string seq_;
  std::vector<uint8_t> scores_;
  SeqType type_;
};

#endif // KLUST_SEQ_ENTRY_H_
