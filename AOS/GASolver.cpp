#include "GASolver.hpp"

using namespace dbt;

GASolver::GASolver(const GASolverParams &params) : AOSSolver(params) {}

std::vector<std::string> GASolver::Solve(llvm::Module *M) {
  std::vector<std::string> OptSequence;
  std::cout << "GA SOLVER RUNNING\n";
  return OptSequence;
}

void GASolver::Evaluate() {}

