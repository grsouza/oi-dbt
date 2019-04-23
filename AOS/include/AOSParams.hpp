#pragma once

#include "llvm/Support/YAMLTraits.h"

#include <iostream>
#include <string>
#include <vector>

namespace dbt {

struct AOSParams {

  bool UpdateDatabase;
  bool CreateDatabase;
  std::string Database;
  bool Training;

  struct SolverParams {
    unsigned Max, Min, Times;
    unsigned Generations;
    unsigned Threshold;
  };

  struct GASolverParams : public SolverParams {};
  struct RMHCSolverParams : public SolverParams {};

  struct ICStrategyType {
    enum ValueType {
      GA,
      RMHC,
    } Value;
    union ParamsType {
      GASolverParams GAParams;
      RMHCSolverParams RMHCParams;
    } Params;
  } ICStrategy;

  enum MCStrategyType {
    CBR,
    DPL,
    RFL,
    LTL,
  } MCStrategy;

  enum CharacterizationStrategyType {
    DNA,
    DND,
    FLL,
  } CharacterizationStrategy;

  enum SimilarityStrategyType {
    NaW,
    CMP,
  } SimilarityStrategy;

  enum RetrieveStrategyType {
    ELITE,
    JUST,
    NEARLY,
  } RetrieveStrategy;

  bool InvokeIC;
};
} // namespace dbt

template <> struct llvm::yaml::MappingTraits<dbt::AOSParams> {
  static void mapping(llvm::yaml::IO &, dbt::AOSParams &);
};

template <>
struct llvm::yaml::ScalarEnumerationTraits<
    dbt::AOSParams::ICStrategyType::ValueType> {
  static void enumeration(llvm::yaml::IO &,
                          dbt::AOSParams::ICStrategyType::ValueType &);
};

template <> struct llvm::yaml::MappingTraits<dbt::AOSParams::GASolverParams> {
  static void mapping(llvm::yaml::IO &io, dbt::AOSParams::GASolverParams &);
};

// template <> struct llvm::yaml::ScalarEnumerationTraits
// <dbt::AOSParams::GASolverParams::InitialSearchSpaceType> {
//   static void
//     enumeration(llvm::yaml::IO &io,
//         dbt::AOSParams::GASolverParams::InitialSearchSpaceType&);
// };

template <> struct llvm::yaml::MappingTraits<dbt::AOSParams::RMHCSolverParams> {
  static void mapping(llvm::yaml::IO &, dbt::AOSParams::RMHCSolverParams &);
};

template <>
struct llvm::yaml::ScalarEnumerationTraits<dbt::AOSParams::MCStrategyType> {
  static void enumeration(llvm::yaml::IO &io, dbt::AOSParams::MCStrategyType &);
};

template <>
struct llvm::yaml::ScalarEnumerationTraits<
    dbt::AOSParams::CharacterizationStrategyType> {
  static void enumeration(llvm::yaml::IO &io,
                          dbt::AOSParams::CharacterizationStrategyType &);
};

template <>
struct llvm::yaml::ScalarEnumerationTraits<
    dbt::AOSParams::RetrieveStrategyType> {
  static void enumeration(llvm::yaml::IO &io,
                          dbt::AOSParams::RetrieveStrategyType &);
};

template <>
struct llvm::yaml::ScalarEnumerationTraits<
    dbt::AOSParams::SimilarityStrategyType> {
  static void enumeration(llvm::yaml::IO &io,
                          dbt::AOSParams::SimilarityStrategyType &);
};