#pragma once

#include "GASolver.hpp"
#include "RMHCSolver.hpp"
#include "llvm/Support/YAMLTraits.h"
#include <iostream>
#include <string>
#include <vector>


namespace dbt {

struct AOSParams {
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
    enum Value {
      GA,
      RMHC,
    } value;
    union Params {
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
  // struct MLStrategy {
  //   enum Value {
  //     /* Case-based reasoning */
  //     CBR,
  //     /* Deep learning */
  //     DPL,
  //     /* Reinforcement learning */
  //     RFL,
  //     /* Long-term learning */
  //     LTL,
  //   } value;
  //   union Params {
  //   } params;
  // } mlStrategy;

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
} // namespace dbt

template <> struct llvm::yaml::MappingTraits<dbt::GASolverParams> {
  static void mapping(llvm::yaml::IO &io, dbt::GASolverParams &params);
};

template <> struct llvm::yaml::MappingTraits<dbt::RMHCSolverParams> {
  static void mapping(llvm::yaml::IO &io, dbt::RMHCSolverParams &params);
};

template <> struct llvm::yaml::MappingTraits<dbt::AOSParams> {
  static void mapping(llvm::yaml::IO &io, dbt::AOSParams &params);
};

template <> struct llvm::yaml::ScalarEnumerationTraits<dbt::AOSParams::ICStrategy::Value> {
  static void enumeration(llvm::yaml::IO &io, dbt::AOSParams::ICStrategy::Value &strategy);
};

template <> struct llvm::yaml::ScalarEnumerationTraits<dbt::AOSParams::RetrieveStrategy> {
  static void enumeration(llvm::yaml::IO &io, dbt::AOSParams::RetrieveStrategy &strategy);
};

template <> struct llvm::yaml::ScalarEnumerationTraits<dbt::AOSParams::SimilarityStrategy> {
  static void enumeration(llvm::yaml::IO &io, dbt::AOSParams::SimilarityStrategy &strategy);
};

template <>
struct llvm::yaml::ScalarEnumerationTraits<dbt::AOSParams::CharacterizationStrategy> {
  static void enumeration(llvm::yaml::IO &io,
                          dbt::AOSParams::CharacterizationStrategy &strategy);
};

template <> 
struct llvm::yaml::ScalarEnumerationTraits<dbt::AOSParams::Report> {
  static void enumeration(llvm::yaml::IO &io, 
                          dbt::AOSParams::Report &report);
};

LLVM_YAML_IS_FLOW_SEQUENCE_VECTOR(dbt::AOSParams::Goal);
template <> struct llvm::yaml::ScalarEnumerationTraits<dbt::AOSParams::Goal> {
  static void enumeration(llvm::yaml::IO &io, dbt::AOSParams::Goal &goal);
};

