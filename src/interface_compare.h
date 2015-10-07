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

#ifndef KLUST_INTERFACE_COMPARE_H_
#define KLUST_INTERFACE_COMPARE_H_

#include "seq_entry.h"

class InterfaceCompare {
 public:
  virtual bool compare(SeqEntry* seq1, SeqEntry* seq2) = 0;

  void setIdentity(float id) { m_identity = id; }
  float getIdentity() const { return m_identity; }

 protected:
  float m_identity; // Similarity identity
};

#endif // KLUST_INTERFACE_COMPARE_H_
