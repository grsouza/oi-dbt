#pragma once

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include <memory>

namespace dbt {

class AOSIROpt {
  std::unique_ptr<llvm::legacy::PassManager> MPM;
  std::unique_ptr<llvm::legacy::FunctionPassManager> FPM;

  void populatePassManager(llvm::legacy::PassManager *MPM,
                           llvm::legacy::FunctionPassManager *FPM,
                           std::vector<std::string> Passes);

public:
  AOSIROpt() {}

  // enum OptLevel { Basic, Soft, Medium, Hard, Custom };

  // void optimizeIRFunction(llvm::Module *M, OptLevel Level);
  void customOptimizeIRFunction(llvm::Module *M, std::vector<std::string> Opts);
};
} // namespace dbt
