#include "RMHCSolver.hpp"

using namespace dbt;

RMHCSolver::RMHCSolver(const RMHCSolverParams &params) : AOSSolver() {}

std::vector<std::string> RMHCSolver::Solve(llvm::Module *M) {
  std::vector<std::string> OptSequence;
  std::cout << "RMHC SOLVER RUNNING\n";
  //maybe return llvm::Module* is better
  return OptSequence;
}

void RMHCSolver::Evaluate() {}
