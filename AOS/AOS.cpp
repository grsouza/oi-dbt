#include "AOS.hpp"

using namespace dbt;

AOSParams::AOSParams(const std::string &filename) {
  // TODO: Parse file with some YAML lib.
}

AOS::AOS(const AOSParams &params) {
  // TODO: Construct AOSSolver from AOSParams
}

void AOS::Run() { solver.Solve(); }