#pragma once

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include <string>

#include <memory>

#define OPT_MIN 0
#define OPT_MAX 6

namespace dbt {
class AOSIROpt {
  std::unique_ptr<llvm::legacy::FunctionPassManager> BasicPM;

  void populateFuncPassManager(llvm::legacy::FunctionPassManager *,
                               std::vector<uint16_t>);

public:
  AOSIROpt(){};

  enum OptLevel { Basic, Soft, Medium, Hard, Custom };

  void optimizeIRFunction(std::shared_ptr<llvm::Module>, std::vector<uint16_t>,
                          OptLevel);
  void customOptimizeIRFunction(llvm::Module *, std::vector<std::string>);
};
} // namespace dbt
