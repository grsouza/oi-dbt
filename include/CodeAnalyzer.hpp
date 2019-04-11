#pragma once

#include "llvm/IR/Module.h"
#include <memory>

namespace dbt {
class CodeAnalyzer {
public:
  CodeAnalyzer() = default;
  double getIPC(std::shared_ptr<llvm::Module> M);
};
} // namespace dbt
