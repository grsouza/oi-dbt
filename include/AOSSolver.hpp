#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "AOSIROpt.hpp"
#include "CodeAnalyzer.hpp"
#include "AOSLog.hpp"

#include "llvm/IR/Module.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/Support/FileSystem.h>

namespace dbt {
  struct AOSSolverParams {};
  class AOSSolver {
  protected:
    std::unique_ptr<AOSIROpt> IRO;
    std::unique_ptr<CodeAnalyzer> CA;
    std::unique_ptr<AOSLog> LOG;
  public:
    AOSSolver() {
      IRO = llvm::make_unique<AOSIROpt>();
      CA = llvm::make_unique<CodeAnalyzer>();
      LOG = std::make_unique<AOSLog>("AOSLog.out");
    }
    virtual ~AOSSolver() {}
    virtual std::vector<std::string> Solve(llvm::Module*) = 0;
    virtual void Evaluate() = 0;
  };
} //namespace dbt
