#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "AOSIROpt.hpp"
#include "AOSLog.hpp"
#include "CodeAnalyzer.hpp"
#include "AOSDataset.hpp"

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include <llvm/Support/FileSystem.h>

namespace dbt {
struct AOSSolverParams {};
class AOSSolver {
protected:
  std::unique_ptr<AOSLog> LOG;

public:
  AOSSolver() { LOG = std::make_unique<AOSLog>("AOSLog.out"); }
  virtual ~AOSSolver() {}
  virtual DatasetFields* Solve(llvm::Module *) = 0;
  virtual void Evaluate() = 0;
};
} // namespace dbt
