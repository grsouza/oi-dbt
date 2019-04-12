#pragma once

#include "llvm/IR/Module.h"
#include <string>

namespace dbt {

class AOSRegionCharacterizationStrategy {
public:
  virtual std::string getCharacterization(const llvm::Module &) = 0;
};

class DNARegionCharacterizationStrategy
    : public AOSRegionCharacterizationStrategy {
public:
  std::string getCharacterization(const llvm::Module &);
};
}; // namespace dbt