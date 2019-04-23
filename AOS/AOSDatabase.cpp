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
  io.mapRequired("CompilationTime", D.CompilationTime);
  io.mapRequired("ExecutionTime", D.ExecutionTime);
}

// void MappingTraits<PopulationData>::mapping(IO &io, PopulationData &D) {
//   io.mapRequired("Generation", D.Generations);
//   io.mapRequired("Chromosomes", D.Chromosomes);
// }

size_t SequenceTraits<std::vector<dbt::Data>>::size(IO &io,
                                                    std::vector<dbt::Data> &D) {
  return D.size();
}

dbt::Data &SequenceTraits<std::vector<dbt::Data>>::element(
    IO &io, std::vector<dbt::Data> &List, size_t Index) {
  return List[Index];
}

// size_t SequenceTraits<std::vector<dbt::PopulationData>>::size(
//     IO &io, std::vector<dbt::PopulationData> &D) {
//   return D.size();
// }

// PopulationData &SequenceTraits<std::vector<dbt::PopulationData>>::element(
//     IO &io, std::vector<dbt::PopulationData> &List, size_t Index) {
//   return List[Index];
// }