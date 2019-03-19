#pragma once

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"

#include "IRJIT.hpp"

#include <cctype>
#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>

namespace dbt {
class CodeAnalyzer {
public:
  static std::string getSymbolicRepresentation(const llvm::Module *);
  static int getSimilarityBetween(const std::string &, const std::string &);

  CodeAnalyzer() {}
  int getStaticSize(std::shared_ptr<llvm::Module>);
  int getDynamicSize(llvm::Module *);
  double getIPC(llvm::Module *);
};
} // namespace dbt
