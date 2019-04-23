#pragma once

#include "AOSDatabase.hpp"
#include "AOSICSolver.hpp"
#include "AOSMLSolver.hpp"
#include "AOSParams.hpp"
#include "AOSRegionCharacterizationStrategy.hpp"
#include "AOSSimilarityStrategy.hpp"
#include "DNA.hpp"
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

struct ROIInfo;

class AOS {

  AOSParams Params;

  std::unique_ptr<AOSICSolver> ICSolver;
  std::unique_ptr<AOSMLSolver> MLSolver;

  std::unique_ptr<AOSRegionCharacterizationStrategy> CTZ;
  unsigned NOR; // Number of Regions
  std::string BinaryName;

public:
  AOS(const std::string &, const std::string &, const std::string &);

  void run(llvm::Module *);
  void run(llvm::Module *, ROIInfo);

  std::unique_ptr<RegionData> makeDatabaseData(DNA *, const std::string &);

  void generateDatabase(std::unique_ptr<RegionData>);
  void loadDatabase();

  bool isTraining() { return Params.Training; }

private:
  void getBinaryName(const std::string &Path);
  void runIC(llvm::Module *M);
  void runML(llvm::Module *M);
};

} // namespace dbt
