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
         const std::string &DatabaseDirectoryPath)
    : Params(Params), Program(Program),
      DatabaseDirectoryPath(DatabaseDirectoryPath) {
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

  t_start = time(nullptr);
  auto SeqOpts = Solver->solve(M);
  t_end = time(nullptr);

  CompileTime = difftime(t_end, t_start);

  Data D;
  D.Program = Program;
  D.DNA = DNARegion;
  D.CompileTime = CompileTime;
  D.SetOpts = SeqOpts;
  D.ExecTime = 0;
  D.History = Solver->getHistory();
  D.ImproveRate = calculateImproveRate(Solver->getHistory());

  Regions.push_back(D);
}

void AOS::run(llvm::Module *M, TestModeInfo T) { this->Solver->Solve(M, T); }

void AOS::generateData() {

  std::ofstream RegionsFile("regions.out");
  std::ofstream DBFile("db.out");

  for (const auto &Region : Regions) {
    RegionsFile << Region.DNA << std::endl << std::endl;
  }

  if (!Regions.empty()) {
    std::string Text;

    llvm::raw_string_ostream Stream(Text);
    llvm::yaml::Output yout(Stream);

    yout << Regions;

    DBFile << Stream.str();
  }

  RegionsFile.close();
  DBFile.close();
}

double AOS::calculateImproveRate(const std::vector<double> &History) {
  double Worst = History[0];
  double Best = History[History.size() - 1];

  return 1 - (Best / Worst);
}
