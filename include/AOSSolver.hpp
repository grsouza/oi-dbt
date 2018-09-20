#pragma once

namespace dbt {

struct AOSSolverParams {};

class AOSSolver {
public:
  AOSSolver() {}
  virtual ~AOSSolver() {}

  virtual void Solve();
  virtual void Evaluate();
};

struct GASolverParams : public AOSSolverParams {
  unsigned numberOfGenerations;
};

class GASolver : public AOSSolver {
public:
  GASolver();
  void Solve() override;
  void Evaluate() override;
};

struct RMHCSolverParams : public AOSSolverParams {
  float mutationRate;
};

class RMHCSolver : public AOSSolver {
public:
  RMHCSolver();

  void Solve() override;
  void Evaluate() override;
};

}; // namespace dbt