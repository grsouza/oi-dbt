#include "AOSDatabase.hpp"

using namespace dbt;

using llvm::yaml::IO;
using llvm::yaml::MappingTraits;
using llvm::yaml::SequenceTraits;

void MappingTraits<RegionData>::mapping(IO &io, RegionData &D) {
  io.mapRequired("DNA", D.DNA);
  io.mapRequired("Best", D.Best);
  io.mapRequired("Historic", D.Historic);
}

void MappingTraits<Data>::mapping(IO &io, Data &D) {
  io.mapRequired("TAs", D.TAs);
  io.mapRequired("IPC", D.IPC);
  io.mapRequired("OptTime", D.OptTime);
  io.mapRequired("ExecutionTime", D.ExecutionTime);
}

size_t SequenceTraits<std::vector<dbt::Data>>::size(IO &io,
                                                    std::vector<dbt::Data> &D) {
  return D.size();
}

dbt::Data &SequenceTraits<std::vector<dbt::Data>>::element(
    IO &io, std::vector<dbt::Data> &List, size_t Index) {
  return List[Index];
}
