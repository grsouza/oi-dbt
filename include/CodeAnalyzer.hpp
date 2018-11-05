#pragma once

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"

#include "IRJIT.hpp"

#include <chrono>
#include <ctime>
#include <cctype>
#include <iostream>
#include <memory>

namespace dbt {
  class CodeAnalyzer {
  public:
    CodeAnalyzer() {}
    int getStaticSize(std::shared_ptr<llvm::Module>); 
    int getDynamicSize(llvm::Module*); 
    double getIPC(llvm::Module*);
  };
} //namespace dbt;
