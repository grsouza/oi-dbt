#ifndef SEARCH_SPACE_HPP
#define SEARCH_SPACE_HPP

#include "AOSPasses.hpp"

namespace dbt {
enum class InitPopType { RANDOM, BEST10, BASELINE };
static std::vector<uint16_t> best10 = {_NONE, LOOP_ROTATE, GVN, MEMCPYOPT,
                                       PRUNE_EH};
static std::vector<uint16_t> baseline = {_NONE, MEM2REG, AA_EVAL};
};
#endif
