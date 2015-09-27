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

#include "main_control.h"

MainControl::MainControl() :
  m_reader(new FastaReader()),
  m_writer(new FastaWriter()),
  m_identity(0.9f)
{
  m_writer->openCoutWriter();
}

MainControl::~MainControl() {
  if(m_reader)
    delete m_reader;
  if(m_writer)
    delete m_writer;
}

MainControl* MainControl::instance() {
  static MainControl control;
  return &control;
}

int MainControl::run() {
  if(m_compare == nullptr || m_clust == nullptr || m_kmergen == nullptr) {
    return EXIT_FAILURE;
  }

  m_compare->setIdentity(m_identity);
  m_clust->setCompare(m_compare);
  m_clust->setKmergen(m_kmergen);

  Sequence seq;
  while(!m_reader->getNextLine(seq)) {
    if(m_clust->addSequence(seq) > 0) {
      m_writer->write(seq);
    }
  }

  return EXIT_SUCCESS;
}

void MainControl::setIdentity(float id) {
  m_identity = id;
}

float MainControl::getIdentity() const {
  return m_identity;
}

void MainControl::setInputFile(const std::string& filename) {
  m_reader->openReader(filename);
}

void MainControl::setOutputFile(const std::string& filename) {
  m_writer->openFileWriter(filename);
}

void MainControl::setKmergen(InterfaceKmergen* kmergen) {
  m_kmergen = kmergen;
}

void MainControl::setCompare(InterfaceCompare* compare) {
  m_compare = compare;
}

void MainControl::setClust(InterfaceClust* clust) {
  m_clust = clust;
}
