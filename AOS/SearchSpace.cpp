#include "SearchSpace.hpp"
#include "llvm/Support/YAMLTraits.h"

using namespace dbt;
using namespace llvm::yaml;

void ScalarEnumerationTraits<InitPopType>::enumeration(IO &io,
                                                       InitPopType &initPop) {
  io.enumCase(initPop, "RANDOM", InitPopType::RANDOM);
  io.enumCase(initPop, "BEST10", InitPopType::BEST10);
  io.enumCase(initPop, "BASELINE", InitPopType::BASELINE);
}