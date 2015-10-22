/*
 * @Author: Andreas Dahl 
 * @Date: 22/10/15
 */

#ifndef KLUST_RESULTTYPES_BASE_RESULT_H_
#define KLUST_RESULTTYPES_BASE_RESULT_H_

#include "../seq_entry.h"

class SequenceResult {
 public:
  enum class ResultType {
    kCentroid,
    kHit
  };

  SequenceResult(SeqEntry* seq, uint32_t clusterNumber, ResultType type);

  ResultType getType();
  SeqEntry* getSequence();
  uint32_t getClusterNumber();

 private:
  ResultType m_type;
  SeqEntry* m_seq;
  uint32_t m_clusterNumber;
};

#endif //KLUST_RESULTTYPES_BASE_RESULT_H_
