#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "AOSDatabase.hpp"
#include "AOSIROpt.hpp"
#include "AOSLog.hpp"
#include "CodeAnalyzer.hpp"

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include <llvm/Support/FileSystem.h>

namespace dbt {
struct TestModeInfo;
struct AOSSolverParams {};
class AOSSolver {
protected:
  std::unique_ptr<AOSLog> LOG;

public:
  AOSSolver() { LOG = std::make_unique<AOSLog>("AOSLog.out"); }

  virtual ~AOSSolver() {}
  virtual std::vector<std::string> Solve(llvm::Module *) = 0;
  virtual void Solve(llvm::Module *, TestModeInfo) = 0;
  virtual void Evaluate() = 0;
};
} // namespace dbt
