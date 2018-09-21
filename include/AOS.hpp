#pragma once

#include "AOSSolver.hpp"
#include "llvm/Support/YAMLTraits.h"
#include <string>
#include <vector>
#include <iostream>

//typedef std::vector<std::string> Threshold;

namespace dbt {

class AOS {
  AOSSolver *solver;
  
public:
  static AOS create(const std::string &filePath);
  void Run() { solver->Solve(); }

  struct Params {
    /* number of times to execute a program, and then calculate the average */
    unsigned times;

    /* update the databse with new insights */
    bool updateDatabase;

    /* path to database file */
    std::string database;

    /* compiler level optimization (or sequence) that will act as baseline */
//    Threshold threshold;

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

    void Dump() const {
      std::cout << "times: " << times << std::endl
                << "updateDatabase: " << updateDatabase << std::endl
                << "database: " << database << std::endl;
/*
      std::cout << "threshold: [";

      for (auto &clo : threshold)
        std::cout << clo << ", ";

      std::cout << "]" << std::endl;
      */

      std::cout << "max: " << max << std::endl
                << "min: " << min << std::endl
                << "onlyOnce: " << onlyOnce << std::endl
                << "roi: " << roi << std::endl;
    }

  };

private:
  AOS(const AOS::Params &params);

};
}; // namespace dbt

  template <>
  struct llvm::yaml::MappingTraits<dbt::AOS::Params> {
    static void mapping(llvm::yaml::IO &io, dbt::AOS::Params &params) {
      io.mapRequired("times", params.times);
      io.mapRequired("updateDatabase", params.updateDatabase);
      io.mapRequired("database", params.database);
      //io.mapRequired("threshold", params.threshold);      
      io.mapRequired("max", params.max);
      io.mapRequired("min", params.min);
      io.mapRequired("onlyOnce", params.onlyOnce);
      io.mapRequired("roi", params.roi);
    }
  };



