#pragma once

#include "AOSParams.hpp"
#include "AOSSolver.hpp"

#include "llvm/IR/Module.h"

namespace dbt {
class AOS {
  AOSSolver *solver;

public:
  static AOS create(const std::string &filePath);
  void run(llvm::Module *);

private:
  AOS(const AOSParams &params);
};
} // namespace dbt
