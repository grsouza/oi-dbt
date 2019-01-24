#pragma once

#include "AOSParams.hpp"
#include "AOSSolver.hpp"

#include "llvm/IR/Module.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/YAMLTraits.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/raw_ostream.h"

#include "manager.hpp"

namespace dbt {
  struct TestModeInfo;
  class AOS {
    AOSSolver *solver;

  public:
    static AOS create(const std::string &filePath);
    void run(llvm::Module *);
    void run(llvm::Module *, TestModeInfo);

  private:
    AOS(const AOSParams &params);
  };
} // namespace dbt
