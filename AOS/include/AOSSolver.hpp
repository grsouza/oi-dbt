#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "AOSDatabase.hpp"
#include "AOSIROpt.hpp"
#include "CodeAnalyzer.hpp"

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include <llvm/Support/FileSystem.h>

namespace dbt {
struct TestModeInfo;

class AOSSolver {
public:
  AOSSolver() = default;

  virtual ~AOSSolver() = default;

  virtual std::vector<std::string> solve(llvm::Module *M) = 0;

  virtual std::vector<double> getHistory() const = 0;

  virtual void Solve(llvm::Module *, TestModeInfo) = 0;
};
} // namespace dbt
