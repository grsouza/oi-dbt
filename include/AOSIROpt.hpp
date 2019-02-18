#pragma once

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include <string>

#include <memory>

namespace dbt {
class AOSIROpt {
  void populateFuncPassManager(llvm::legacy::FunctionPassManager *,
                               std::vector<uint16_t>);

public:
  AOSIROpt(){};

  enum OptLevel { Basic, Soft, Medium, Hard, Custom };

  void optimizeIRFunction(std::shared_ptr<llvm::Module>, std::vector<uint16_t>,
                          OptLevel);
  void optimizeIRFunction(llvm::Module *M, std::vector<uint16_t>, OptLevel);
};
} // namespace dbt
