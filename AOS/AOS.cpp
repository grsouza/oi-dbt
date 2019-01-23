#include "AOS.hpp"
#include "AOSParams.hpp"

#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/YAMLTraits.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/raw_ostream.h"

#include "AOSDataset.hpp"

#include <iostream>
#include <string>

using llvm::yaml::Output;

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
  auto Obj = this->solver->Solve(M);
  
  std::string Text;
  llvm::raw_string_ostream Stream(Text);
  llvm::yaml::Output yout(Stream);
  yout << *Obj;

  std::cout << Stream.str() << std::endl;
}
