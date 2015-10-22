/*
 * @Author: Andreas Dahl 
 * @Date: 22/10/15
 */

#include "sequence_result.h"

SequenceResult::SequenceResult(SeqEntry* seq, uint32_t clusterNumber, ResultType type) {
  this->m_seq = seq;
  this->m_clusterNumber = clusterNumber;
  this->m_type = type;
}

SequenceResult::ResultType SequenceResult::getType() {
  return m_type;
}

SeqEntry* SequenceResult::getSequence() {
  return m_seq;
}

uint32_t SequenceResult::getClusterNumber() {
  return m_clusterNumber;
}
