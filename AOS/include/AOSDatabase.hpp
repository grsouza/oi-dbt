#pragma once

#include <string>
#include <vector>

#include "llvm/Support/YAMLTraits.h"

using llvm::yaml::IO;
using llvm::yaml::MappingTraits;

namespace dbt {

struct Data {
  std::vector<std::string> TAs;
  double IPC;
  double CompilationTime;
  double ExecutionTime;
};

struct RegionData {
  std::string DNA;
  std::vector<Data> Historic;
  Data Best;
};

} // namespace dbt

template <> struct llvm::yaml::MappingTraits<dbt::RegionData> {
  static void mapping(llvm::yaml::IO &, dbt::RegionData &);
};

template <> struct llvm::yaml::MappingTraits<dbt::Data> {
  static void mapping(llvm::yaml::IO &, dbt::Data &);
};

// template <> struct llvm::yaml::MappingTraits<dbt::PopulationData> {
//   static void mapping(llvm::yaml::IO&, dbt::PopulationData&);
// };

template <> struct llvm::yaml::SequenceTraits<std::vector<dbt::Data>> {
  static size_t size(llvm::yaml::IO &, std::vector<dbt::Data> &);
  static dbt::Data &element(llvm::yaml::IO &, std::vector<dbt::Data> &, size_t);
};

// template <>
// struct llvm::yaml::SequenceTraits<std::vector<dbt::PopulationData>> {
//   static size_t size(llvm::yaml::IO &, std::vector<dbt::PopulationData> &);
//   static dbt::PopulationData &
//   element(llvm::yaml::IO &, std::vector<dbt::PopulationData> &, size_t);
// };