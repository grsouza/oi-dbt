#pragma once

#include "llvm/IR/Module.h"
#include <string>

namespace dbt {

class AOSRegionCharacterizationStrategy {
public:
  virtual std::string encode(const llvm::Module &) = 0;
};

class DNARegionCharacterizationStrategy
    : public AOSRegionCharacterizationStrategy {
public:
  std::string encode(const llvm::Module &);
};
}; // namespace dbt