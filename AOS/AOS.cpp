#include "AOS.hpp"
#include "AOSDatabase.hpp"
#include "AOSParams.hpp"
#include "RMHCSolver.hpp"

#include <iostream>
#include <string>
#include <time.h>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

using llvm::yaml::Output;

using namespace dbt;

AOS::AOS(const std::string &AOSFilePath, const std::string &BinaryPath,
         const std::string &BinaryArgs) {
  auto InputBuffer = llvm::MemoryBuffer::getFile(AOSFilePath);
  llvm::yaml::Input yin(InputBuffer->get()->getBuffer());

  yin >> Params;

  if (yin.error()) {
    std::cerr << yin.error().message() << std::endl;
    exit(1);
  }

  switch (Params.ICStrategy.Value) {
  case AOSParams::ICStrategyType::ValueType::RMHC:
    ICSolver =
        std::make_unique<RMHCSolver>(Params.ICStrategy.Params.RMHCParams);
    break;

  case AOSParams::ICStrategyType::ValueType::GA:
    assert(false && "Strategy not supported");
    break;
  }

  switch (Params.SimilarityStrategy) {
  case AOSParams::SimilarityStrategyType::NaW:
    // SimilarityStrategy = std::make_unique<NWAOSSimilarityStrategy>();
    break;

  case AOSParams::SimilarityStrategyType::CMP:
    assert(false && "Strategy not supported.");
  }

  switch (Params.CharacterizationStrategy) {
  case AOSParams::CharacterizationStrategyType::DNA:
    CTZ = std::make_unique<DNARegionCharacterizationStrategy>();
    break;

  case AOSParams::CharacterizationStrategyType::DND:
    assert(false && "Strategy not supported.");
    break;

  case AOSParams::CharacterizationStrategyType::FLL:
    assert(false && "Strategy not supported.");
    break;
  }

  getBinaryName(BinaryPath);

  // if (Params.Training && Params.CreateDatabase) {
  // } else if (!Params.Training) {
  // }
}

void AOS::getBinaryName(const std::string &Path) {
  int Index = -1;

  BinaryName = "";

  for (unsigned i = 0; i < Path.size(); ++i) {
    if (Path[i] == '/')
      Index = i;
  }

  if (Index == -1) {
    BinaryName += Path;
  } else {
    for (unsigned i = Index + 1; i < Path.size(); ++i) {
      BinaryName += Path[i];
    }
  }
}

void AOS::run(llvm::Module *M) {
  NOR++;

  if (Params.Training) {
    runIC(M);
  } else {
    runML(M);
  }
}

void AOS::runIC(llvm::Module *M) {
  std::string DNA = CTZ->encode(*M);
  auto ICData = ICSolver->solve(M, NOR);

  auto RD = std::make_unique<RegionData>();
  RD->DNA = DNA;
  RD->Best.TAs = ICData->getGenes();
  RD->Best.IPC = ICData->getFitness();

  generateDatabase(std::move(RD));
}

void AOS::runML(llvm::Module *M) {}

void AOS::run(llvm::Module *M, ROIInfo R) {
  NOR++;
  ICSolver->solve(M, R, NOR);
}

void AOS::generateDatabase(std::unique_ptr<RegionData> RD) {
  std::ofstream File;
  std::string Text;

  std::string FileName =
      Params.Database + BinaryName + std::to_string(NOR) + ".yaml";
  File.open(FileName, std::fstream::app);

  if (!File) {
    exit(1);
  }

  llvm::raw_string_ostream Stream(Text);
  llvm::yaml::Output yout(Stream);

  yout << *(RD.get());
  File << Stream.str();

  File.close();
}

void AOS::loadDatabase() {
  RegionData RD;

  for (const auto &Entry : fs::directory_iterator(Params.Database)) {
    auto InputBuffer = llvm::MemoryBuffer::getFile(Entry.path().c_str());
    llvm::yaml::Input yin(InputBuffer->get()->getBuffer());

    yin >> RD;

    std::cout << RD.DNA << std::endl;
    std::cout << RD.Best.TAs.size() << std::endl;
  }
}