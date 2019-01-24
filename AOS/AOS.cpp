#include <iostream>
#include <string>
#include <time.h>

#include "AOS.hpp"
#include "AOSParams.hpp"
#include "AOSDatabase.hpp"

using llvm::yaml::Output;

using namespace dbt;

AOS AOS::create(const std::string &filePath, const std::string &program) {
  auto InputBuffer = llvm::MemoryBuffer::getFile(filePath);
  llvm::yaml::Input yin(InputBuffer->get()->getBuffer());

  AOSParams params;
  yin >> params;

  if (yin.error()) {
    std::cerr << yin.error().message() << std::endl;
  }

  return AOS(params, program);
}

AOS::AOS(const AOSParams &params, const std::string &program) {
  Params = params;
  Program = program;
  switch (params.icStrategy.value) {
  case AOSParams::ICStrategy::GA:
    this->solver = new GASolver(params.icStrategy.params.ga);
    break;
  case AOSParams::ICStrategy::RMHC:
    this->solver = new RMHCSolver(params.icStrategy.params.rmhc);
    break;
  }
}

void AOS::run(llvm::Module *M) {
  float CompileTime;
  time_t t_start, t_end;
  
  t_start = time(NULL);
  auto SeqOpts = this->solver->Solve(M);
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
 
void AOS::run(llvm::Module *M, TestModeInfo T) {
  this->solver->Solve(M, T);
}

void AOS::generateData() {
  if(Regions.size() > 0) {
    std::ofstream file;
    std::string Text;
    
    if(Params.updateDatabase) {
      file.open(Params.database, std::fstream::app);
    }else if(Params.createDatabase) {
      file.open(Params.database);
    }
    
    llvm::raw_string_ostream Stream(Text);
    llvm::yaml::Output yout(Stream);
    
    yout << Regions;

    file << Stream.str();
  }
}
