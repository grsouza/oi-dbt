#pragma once

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"

#include "IRJIT.hpp"

#include <chrono>
#include <ctime>

namespace dbt {
  class CodeAnalyzer {
  public:
    CodeAnalyzer() { 
    }
    double getIPC(llvm::Module *M);
  };
} //namespace dbt;
