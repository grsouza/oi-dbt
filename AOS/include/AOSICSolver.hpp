#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "AOSDatabase.hpp"
#include "AOSIROpt.hpp"
#include "CodeAnalyzer.hpp"
#include "DNA.hpp"

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include <llvm/Support/FileSystem.h>

namespace dbt {
struct ROIInfo;

/// Base class for iterative compilation strategies.
class AOSICSolver {
public:
  AOSICSolver() = default;
  virtual ~AOSICSolver() = default;
  virtual std::unique_ptr<DNA> solve(llvm::Module *M, unsigned) = 0;
  virtual void solve(llvm::Module *, ROIInfo, unsigned) = 0;

  virtual std::vector<double> getHistory() = 0;
};
} // namespace dbt
