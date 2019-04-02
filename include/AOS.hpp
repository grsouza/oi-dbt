#pragma once

#include "AOSParams.hpp"
#include "AOSRegionCharacterizationStrategy.hpp"
#include "AOSSimilarityStrategy.hpp"
#include "AOSSolver.hpp"
#include "manager.hpp"

#include "llvm/ADT/SmallString.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/YAMLTraits.h"
#include "llvm/Support/raw_ostream.h"

namespace dbt {

struct TestModeInfo;

class AOS {
  AOSParams Params;
  std::string Program;
  std::string DatabaseFilePath;
  std::unique_ptr<AOSSolver> Solver;
  std::unique_ptr<AOSSimilarityStrategy> SimilarityStrategy;
  std::unique_ptr<AOSRegionCharacterizationStrategy>
      RegionCharacterizationStrategy;
  std::vector<Data> Regions;

public:
  static AOS create(const std::string &, const std::string &,
                    const std::string &);

  void run(llvm::Module *);
  void run(llvm::Module *, TestModeInfo);
  void generateData();

private:
  AOS(const AOSParams &, const std::string &, const std::string &);
};

} // namespace dbt
