#pragma once

#include <string>
#include <vector>

#include "llvm/Support/YAMLTraits.h"

using llvm::yaml::IO;
using llvm::yaml::MappingTraits;

namespace dbt {
struct Data {
  std::string Program;
  std::string DNA;
  std::vector<uint16_t> SetOpts;
  float CompileTime;
  float ExecTime;
};
} // namespace dbt

LLVM_YAML_IS_SEQUENCE_VECTOR(dbt::Data)

template <> struct llvm::yaml::MappingTraits<dbt::Data> {
  static void mapping(llvm::yaml::IO &io, dbt::Data &Params);
};
