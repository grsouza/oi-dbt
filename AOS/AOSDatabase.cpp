#include "AOSDatabase.hpp"

using namespace dbt;

void MappingTraits<Data>::mapping(IO &io, Data &Params) {
  io.mapRequired("Program", Params.Program);
  io.mapRequired("DNA", Params.DNA);
  io.mapRequired("SetOpts", Params.SetOpts);
  io.mapRequired("CompileTime", Params.CompileTime);
  io.mapRequired("ExecTime", Params.ExecTime);
}
