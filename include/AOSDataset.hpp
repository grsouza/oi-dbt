#pragma once

#include <string>
#include <vector>

#include "llvm/Support/YAMLTraits.h"

using llvm::yaml::MappingTraits;
using llvm::yaml::IO;

namespace dbt {
  struct DatasetFields {
    std::string DNA;
    std::vector<uint16_t> SetOpts;
    float CompileTime;
    float ExecTime;
  };
}

template <> struct llvm::yaml::MappingTraits<dbt::DatasetFields> {
  static void mapping(llvm::yaml::IO &io, dbt::DatasetFields &Params);
};
