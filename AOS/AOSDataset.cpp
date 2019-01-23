#include "AOSDataset.hpp"

using namespace dbt;

void MappingTraits<DatasetFields>::mapping(IO &io, DatasetFields &Params) {
  io.mapRequired("DNA", Params.DNA);
  io.mapRequired("SetOpts", Params.SetOpts);
  io.mapRequired("compileTime", Params.CompileTime);
  io.mapRequired("ExecTime", Params.ExecTime);
}
