#pragma once

#include <string>

namespace dbt {

class AOSSimilarityStrategy {

public:
  virtual int getSimilarityBetween(const std::string &A,
                                   const std::string &B) = 0;
};

class NWAOSSimilarityStrategy : public AOSSimilarityStrategy {

public:
  int getSimilarityBetween(const std::string &A, const std::string &B);
};

}; // namespace dbt