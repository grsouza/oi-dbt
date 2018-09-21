#pragma once
#include <string>
#include <vector>

namespace dbt {

struct AOSSolverParams {};

class AOSSolver {
public:
  AOSSolver(const AOSSolverParams &params) {}
  virtual ~AOSSolver() {}

  virtual std::vector<std::string> Solve() = 0;
  virtual void Evaluate() = 0;
};
}; // namespace dbt
