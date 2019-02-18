#include "AOS.hpp"
#include "AOSDatabase.hpp"
#include "AOSParams.hpp"
#include <iostream>
#include <string>
#include <time.h>

using llvm::yaml::Output;

using namespace dbt;

AOS AOS::create(const std::string &FilePath, const std::string &Program) {
  auto InputBuffer = llvm::MemoryBuffer::getFile(FilePath);
  llvm::yaml::Input yin(InputBuffer->get()->getBuffer());

  AOSParams Params;
  yin >> Params;

  if (yin.error()) {
    std::cerr << yin.error().message() << std::endl;
  }

  return AOS(Params, Program);
}

AOS::AOS(const AOSParams &Params, const std::string &Program)
    : Params(Params), Program(Program) {
  switch (Params.icStrategy.value) {
  case AOSParams::ICStrategy::GA:
    this->Solver = new GASolver(Params.icStrategy.params.ga);
    break;

  case AOSParams::ICStrategy::RMHC:
    this->Solver = new RMHCSolver(Params.icStrategy.params.rmhc);
    break;
  }
}

void AOS::run(llvm::Module *M) {
  float CompileTime;
  time_t t_start, t_end;

  t_start = time(NULL);
  auto SeqOpts = this->Solver->Solve(M);
  t_end = time(NULL);

  CompileTime = difftime(t_end, t_start);
  std::string DNARegion = CodeAnalyzer::getSymbolicRepresentation(M);

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
