#pragma once

#include "llvm/IR/Module.h"
#include <memory>

namespace dbt {
class CodeAnalyzer {
public:
  CodeAnalyzer() = default;
  static double getIPC(const std::shared_ptr<llvm::Module> &M);

};
} // namespace dbt