#include "RMHCSolver.hpp"

using namespace dbt;

RMHCSolver::RMHCSolver(const RMHCSolverParams &params)
    : AOSSolver(params), params(params) {}

std::vector<std::string> RMHCSolver::Solve(llvm::Module *M) {

  // TODO:
  // 1. Choose an initial DNA as the current best-evaluated DNA and evaluate its
  // fitness
  // 2. Choose a locus at random to mutate on this DNA.
  // 3. Evaluate the fitness of the new DNA. If it leads to better fitness, set
  // it as the best-evaluated DNA, if not, give it up.
  // 4. If the fitness reaches the threshold return a the best evaluated DNA, if
  // not return step 2.

  std::vector<std::string> bestEvaluated = {"instcombine",
                                            "simplifycfg",
                                            "reassociate",
                                            "gvn",
                                            "die",
                                            "dce",
                                            "instcombine",
                                            "licm",
                                            "memcpyopt",
                                            "loop-unswitch",
                                            "instcombine",
                                            "indvars",
                                            "loop-deletion",
                                            "loop-predication",
                                            "loop-unroll",
                                            "simplifycfg",
                                            "instcombine",
                                            "licm",
                                            "gvn"};

  unsigned bestEvaluatedFitness = fitness(bestEvaluated);
  for (unsigned currentGeneration = 0; currentGeneration < params.generations;
       ++currentGeneration) {
    std::vector<std::string> newSequence = mutate(bestEvaluated);
    unsigned newSequenceFitness = fitness(newSequence);

    if (newSequenceFitness > bestEvaluatedFitness) {
      bestEvaluatedFitness = newSequenceFitness;
      bestEvaluated = newSequence;
    }
  }

  return bestEvaluated;
}

void RMHCSolver::Evaluate() {}

std::vector<std::string>
RMHCSolver::mutate(const std::vector<std::string> &sequence) {
  unsigned idx1;
  unsigned idx2;

  do {
    idx1 = rand() % sequence.size();
    idx2 = rand() % sequence.size();
  } while (idx1 == idx2);

  std::vector<std::string> newSequence = sequence;
  std::string tmp = newSequence[idx1];
  newSequence[idx1] = newSequence[idx2];
  newSequence[idx2] = tmp;

  return newSequence;
}

unsigned RMHCSolver::fitness(const std::vector<std::string> &sequence) {}