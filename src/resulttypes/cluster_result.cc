/*
 * @Author: Andreas Dahl 
 * @Date: 22/10/15
 */

#include "sequence_result.h"
#include "cluster_result.h"

ClusterResult::ClusterResult(uint32_t clusterNumber)
  : m_clusterNumber(clusterNumber),
    m_sequenceCount(1)
{
}

uint32_t ClusterResult::getSequenceCount() {
  return m_sequenceCount;
}

uint32_t ClusterResult::getClusterNumber() {
  return m_clusterNumber;
}

void ClusterResult::incrementCount() {
  ++m_sequenceCount;
}

void ClusterResult::incrementCount(uint32_t n) {
  m_sequenceCount += n;
}
