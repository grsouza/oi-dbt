#ifndef SEARCH_SPACE_HPP
#define SEARCH_SPACE_HPP

#include "AOSPasses.hpp"
#include "llvm/Support/YAMLTraits.h"
#include <cstdint>
#include <vector>

using namespace llvm::yaml;

namespace dbt {

enum class SearchSpaceType { RANDOM, BEST10, BASELINE };

static std::vector<uint16_t> best10 = {_NONE, LOOP_ROTATE, GVN, MEMCPYOPT};
static std::vector<uint16_t> baseline = {_NONE, MEM2REG};

} // namespace dbt

template <> struct llvm::yaml::ScalarEnumerationTraits<dbt::SearchSpaceType> {
  static void enumeration(llvm::yaml::IO &io, dbt::SearchSpaceType &InitSpace);
};

#endif
