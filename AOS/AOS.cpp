#include "AOS.hpp"
#include "AOSDatabase.hpp"
#include "AOSParams.hpp"
#include <iostream>
#include <string>
#include <time.h>

using llvm::yaml::Output;

using namespace dbt;

AOS AOS::create(const std::string &FilePath, const std::string &Program,
                const std::string &DatabaseFilePath) {
  auto InputBuffer = llvm::MemoryBuffer::getFile(FilePath);
  llvm::yaml::Input yin(InputBuffer->get()->getBuffer());

  AOSParams Params;
  yin >> Params;

  if (yin.error()) {
    std::cerr << yin.error().message() << std::endl;
  }

  return AOS(Params, Program, DatabaseFilePath);
}

AOS::AOS(const AOSParams &Params, const std::string &Program,
         const std::string &DatabaseFilePath)
    : Params(Params), Program(Program), DatabaseFilePath(DatabaseFilePath) {
  switch (Params.icStrategy.value) {
    // case AOSParams::ICStrategy::GA:
    //   this->Solver = std::make_unique<GASolver>(Params.icStrategy.params.ga);
    //   break;

  case AOSParams::ICStrategy::RMHC:
    this->Solver = std::make_unique<RMHCSolver>(Params.icStrategy.params.rmhc);
    break;
  }

  switch (Params.similarity) {
  case AOSParams::SimilarityStrategy::NAW:
    this->SimilarityStrategy = std::make_unique<NWAOSSimilarityStrategy>();
    break;

  case AOSParams::SimilarityStrategy::CMP:
    assert(false && "Strategy not supported.");
  }

  switch (Params.characterization) {
  case AOSParams::CharacterizationStrategy::DNA:
    this->RegionCharacterizationStrategy =
        std::make_unique<DNARegionCharacterizationStrategy>();
    break;

  case AOSParams::CharacterizationStrategy::DND:
    assert(false && "Strategy not supported.");
    break;

  case AOSParams::CharacterizationStrategy::FLL:
    assert(false && "Strategy not supported.");
    break;
  }
}

void AOS::run(llvm::Module *M) {
  float CompileTime;
  time_t t_start, t_end;

  std::string DNARegion =
      RegionCharacterizationStrategy->getCharacterization(*M);

  // std::cout << "Region DNA:" << std::endl << DNARegion << std::endl;

  t_start = time(NULL);
  auto SeqOpts = this->Solver->Solve(M);
  t_end = time(NULL);

  CompileTime = difftime(t_end, t_start);

  // if (Regions.size() > 1) {
  //   int Similarity = SimilarityStrategy->getSimilarityBetween(
  //       DNARegion, Regions[Regions.size() - 1].DNA);
  //   std::cout << "Similarity: " << Similarity << std::endl;
  // }

  Data D;
  D.Program = Program;
  D.DNA = DNARegion;
  D.CompileTime = CompileTime;
  D.SetOpts = SeqOpts;
  D.ExecTime = 0;

  Regions.push_back(D);
}

void AOS::run(llvm::Module *M, TestModeInfo T) { this->Solver->Solve(M, T); }

void AOS::generateData() {

  // std::ofstream File(DatabaseFilePath);

  // for (int i = 0; i < Regions.size(); ++i) {
  //   File << i << std::endl << Regions[i].DNA << std::endl << std::endl;
  // }

  // File.close();

  if (Regions.size() > 0) {
    std::ofstream File;
    std::string Text;

    if (Params.updateDatabase) {
      File.open(Params.database, std::fstream::app);
    } else if (Params.createDatabase) {
      File.open(Params.database);
    }

    llvm::raw_string_ostream Stream(Text);
    llvm::yaml::Output yout(Stream);

    yout << Regions;

    File << Stream.str();
  }
}
