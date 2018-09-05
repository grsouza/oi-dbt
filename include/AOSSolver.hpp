#pragma once

namespace dbt {
class AOSSolver {
public:
  AOSSolver() {}
  virtual ~AOSSolver() {}

  virtual void Solve();
  virtual void Evaluate();
};

class GA_AOSSolver : public AOSSolver {
public:
  GA_AOSSolver();
  void Solve();
};

class RMHCSolver : public AOSSolver {};

}; // namespace dbt