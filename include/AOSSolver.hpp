#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "llvm/IR/Module.h"

namespace dbt {
  struct AOSSolverParams {};

  class AOSSolver {
  public:
    AOSSolver(const AOSSolverParams &params) {}
    virtual ~AOSSolver() {}

    virtual std::vector<std::string> Solve(llvm::Module *M) = 0;
    virtual void Evaluate() = 0;
  };
} // namespace dbt
