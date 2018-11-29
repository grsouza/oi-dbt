#include "SearchSpace.hpp"
#include "llvm/Support/YAMLTraits.h"

using namespace dbt;
using namespace llvm::yaml;

void ScalarEnumerationTraits<SearchSpaceType>::enumeration(IO &io,
                                                       SearchSpaceType &InitSpace) {
  io.enumCase(InitSpace, "RANDOM", SearchSpaceType::RANDOM);
  io.enumCase(InitSpace, "BEST10", SearchSpaceType::BEST10);
  io.enumCase(InitSpace, "BASELINE", SearchSpaceType::BASELINE);
}

