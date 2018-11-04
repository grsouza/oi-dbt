#include "AOS.hpp"
#include "AOSParams.hpp"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/YAMLTraits.h"

#include <iostream>

using namespace dbt;

AOS AOS::create(const std::string &filePath) {
  auto InputBuffer = llvm::MemoryBuffer::getFile(filePath);
  llvm::yaml::Input yin(InputBuffer->get()->getBuffer());

  AOSParams params;
  yin >> params;

  if (yin.error()) {
    std::cerr << yin.error().message() << std::endl;
  }
  
  return AOS(params);
}

AOS::AOS(const AOSParams &params) {
  // TODO: Construct AOSSolver from params
  switch(params.icStrategy.value) {
    case AOSParams::ICStrategy::GA:
      this->solver = new GASolver(params.icStrategy.params.ga);
      break;
    case AOSParams::ICStrategy::RMHC:
      this->solver = new RMHCSolver(params.icStrategy.params.rmhc);
      break;
  }
}

void AOS::run(llvm::Module *M) {
  this->solver->Solve(M);
}
