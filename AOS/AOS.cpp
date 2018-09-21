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

  //  switch (params.icStrategy.stragegy) {
  //  case AOS::Params::ICStrategy::GA:
  //    std::cout << "Number of generations: "
  //              << params.icStrategy.params.ga.numberOfGenerations <<
  //              std::endl;
  //    break;
  //
  //  case AOS::Params::ICStrategy::RMHC:
  //    std::cout << "Mutation rate: " <<
  //    params.icStrategy.params.rmhc.mutationRate
  //              << std::endl;
  //  }
}

void AOS::Run() {
  // std::vector<std::string> OptSequence = solver->Solve();
  // for (auto &opt : OptSequence)
  //   std::cout << opt << std::endl;
}
