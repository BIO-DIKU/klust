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

#ifndef KLUST_MAIN_CONTROL_H
#define KLUST_MAIN_CONTROL_H

#include <string>

#include "fasta_reader.h"
#include "fasta_writer.h"
#include "interface_compare.h"
#include "interface_clust.h"
#include "interface_kmergen.h"

class MainControl {
 private:
  MainControl(const MainControl&) = delete;
  MainControl& operator=(const MainControl&) = delete;

  MainControl();

 public:
  virtual ~MainControl();

  static MainControl* instance();
  int run();

  void setIdentity(float id);
  float getIdentity() const;

  void setInputFile(const std::string& filename);
  void setOutputFile(const std::string& filename);

  void setKmergen(InterfaceKmergen* kmergen);
  void setCompare(InterfaceCompare* compare);
  void setClust(InterfaceClust* clust);

 private:
  FastaReader* m_reader;
  FastaWriter* m_writer;

  float m_identity; // Similarity identity

  InterfaceKmergen* m_kmergen;
  InterfaceCompare* m_compare;
  InterfaceClust* m_clust;
};

#endif // KLUST_MAIN_CONTROL_H
