#pragma once

#include "AOSParams.hpp"
#include "AOSSimilarityStrategy.hpp"
#include "AOSSolver.hpp"

#include "llvm/ADT/SmallString.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/YAMLTraits.h"
#include "llvm/Support/raw_ostream.h"

#include "manager.hpp"

namespace dbt {

struct TestModeInfo;

class AOS {
  AOSParams Params;
  std::string Program;
  std::unique_ptr<AOSSolver> Solver;
  std::unique_ptr<AOSSimilarityStrategy> SimilarityStrategy;
  std::vector<Data> Regions;

public:
  static AOS create(const std::string &, const std::string &);
  
  void run(llvm::Module *);
  void run(llvm::Module *, TestModeInfo);
  void generateData();

private:
  AOS(const AOSParams &, const std::string &);
};

} // namespace dbt
