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

#include "seq_entry.h"

SeqEntry::SeqEntry() : type_(SeqType::nucleotide) {
}

SeqEntry::SeqEntry(const std::string& name, const std::string& sequence,
                   const std::vector<uint8_t>& scores, SeqEntry::SeqType sequence_type)
    : name_(name),
      seq_(sequence),
      scores_(scores),
      type_(sequence_type) {
}

SeqEntry SeqEntry::SubSeq(size_t i, size_t len) const {
  return SeqEntry(name(), seq().substr(i, len), scores(), type());
}
