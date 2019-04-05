#pragma once

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"

namespace dbt {
class AOSIROpt {
  std::unique_ptr<llvm::legacy::PassManager> BasicMPM;
  std::unique_ptr<llvm::legacy::FunctionPassManager> BasicFPM;

  void populatePassManager(llvm::legacy::PassManager *,
                           llvm::legacy::FunctionPassManager *,
                           std::vector<std::string>);

public:
  AOSIROpt() = default;

  enum OptLevel { Basic, Soft, Medium, Hard, Custom };

  void optimizeIRFunction(llvm::Module *, OptLevel);
  void customOptimizeIRFunction(llvm::Module *, std::vector<std::string>);
};
} // namespace dbt
