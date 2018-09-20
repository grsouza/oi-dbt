#pragma once

#include "AOSSolver.hpp"

namespace dbt {

class AOS {
  AOSSolver *solver;

public:
  static AOS create(const char *filePath);
  void Run() { solver->Solve(); }

private:
  struct Params {
    /* number of times to execute a program, and then calculate the average */
    unsigned times;

    /* update the databse with new insights */
    bool updateDatabase;

    /* path to database file */
    std::string database;

    /* compiler level optimization (or sequence) that will act as baseline */
    std::vector<std::string> threshold;

    /* max sequence length */
    unsigned max;

    /* min sequence length */
    unsigned min;

    /* optimization appears only once */
    bool onlyOnce;

    /* region of interest */
    unsigned roi;

    struct ICStrategy {
      enum {
        GA,
        RMHC,
      } stragegy;

      union {
        GASolverParams ga;
        RMHCSolverParams rmhc;
      } params;
    } icStrategy;

    /* the goal of the compiler */
    enum Goal {
      RUNTIME,
      SIZE,
      ENERGY,
    };
    std::vector<Goal> objetive;

    /* indicates if it should create a database */
    bool createDatabase;

    /* create a final report */
    enum Report {
      SIMPLE,
      DETAILED,
      NONE,
    } report;

    /* use iterative compilation as a training phase */
    bool training;

    /* the training programs */
    std::vector<std::string> trainingPrograms;

    /* Machine Learning strategy */
    enum MLStrategy {
      /* Case-based reasoning */
      CBR,
      /* Deep learning */
      DPL,
      /* Reinforcement learning */
      RFL,
      /* Long-term learning */
      LTL,
    } mlStrategy;

    /* strategy used to represent regions */
    enum CharacterizationStrategy {
      /* DNA-based approach (only the OpenISA instructions) */
      DNA,

      /* DNA-based aproach (OpenISA instructions + data type) */
      DND,

      /* The complete region */
      FLL,
    } characterization;

    /* strategy used to find similar regions */
    enum SimilarityStrategy {
      /* Needleman-Wunsh algorithm */
      NAW,
      /* Compress */
      CMP,
    } similarity;

    /* strategy used to retrieve sequences */
    enum RetrieveStrategy {
      ELITE,
      JUST,
      NEARLY,
    } retrieve;

    /* invoke an iterative compilation strategy in a second round */
    bool invokeIC;
  };

  AOS(const Params &params);
};
}; // namespace dbt