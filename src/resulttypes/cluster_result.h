/*
 * @Author: Andreas Dahl 
 * @Date: 22/10/15
 */

#ifndef KLUST_RESULTTYPES_CLUSTER_RESULT_H_
#define KLUST_RESULTTYPES_CLUSTER_RESULT_H_

#include "sequence_result.h"

class ClusterResult {
 public:
  ClusterResult(uint32_t clusterNumber);

  // Accessors
  uint32_t getSequenceCount();
  uint32_t getClusterNumber();

  void incrementCount();
  void incrementCount(uint32_t n);

 private:
  uint32_t m_clusterNumber;
  uint32_t m_sequenceCount;
};

#endif  //KLUST_RESULTTYPES_CLUSTER_RESULT_H_
