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
struct ROIInfo;

class AOSICSolver {
public:
  AOSICSolver() = default;
  virtual ~AOSICSolver() = default;
  virtual std::vector<std::string> solve(llvm::Module *M, unsigned) = 0;
  virtual void solve(llvm::Module *, ROIInfo, unsigned) = 0;
};
} // namespace dbt
