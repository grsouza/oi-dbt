#include "AOSParams.hpp"
#include "llvm/Support/YAMLTraits.h"

using namespace dbt;
using namespace llvm::yaml;

void MappingTraits<AOSParams>::mapping(IO &io, AOSParams &Params) {
  io.mapRequired("updateDatabase", Params.UpdateDatabase);
  io.mapRequired("createDatabase", Params.CreateDatabase);
  io.mapRequired("training", Params.Training);
  io.mapRequired("database", Params.Database);
  io.mapRequired("icStrategy", Params.ICStrategy.Value);

  switch (Params.ICStrategy.Value) {
  case AOSParams::ICStrategyType::ValueType::GA:
    io.mapRequired("icStrategyParams", Params.ICStrategy.Params.GAParams);
    break;
  case AOSParams::ICStrategyType::ValueType::RMHC:
    io.mapRequired("icStrategyParams", Params.ICStrategy.Params.RMHCParams);
  }

  io.mapRequired("mcStrategy", Params.MCStrategy);
  io.mapRequired("characterization", Params.CharacterizationStrategy);
  io.mapRequired("retrieving", Params.RetrieveStrategy);
  io.mapRequired("similarity", Params.SimilarityStrategy);
  io.mapRequired("invokeIC", Params.InvokeIC);
}

void ScalarEnumerationTraits<AOSParams::ICStrategyType::ValueType>::enumeration(
    IO &io, AOSParams::ICStrategyType::ValueType &Strategy) {
  io.enumCase(Strategy, "GA", AOSParams::ICStrategyType::ValueType::GA);
  io.enumCase(Strategy, "RMHC", AOSParams::ICStrategyType::ValueType::RMHC);
}

void MappingTraits<AOSParams::GASolverParams>::mapping(
    IO &io, AOSParams::GASolverParams &Params) {
  io.mapRequired("max", Params.Max);
  io.mapRequired("min", Params.Min);
  io.mapRequired("times", Params.Times);
  io.mapRequired("generations", Params.Generations);
  io.mapRequired("threshold", Params.Threshold);
}

// void ScalarEnumerationTraits<
//     AOSParams::GASolverParams::InitialSearchSpaceType>::
//     enumeration(IO &io,
//                 AOSParams::GASolverParams::InitialSearchSpaceType &Space) {
//   io.enumCase(Space, "RANDOM",
//               AOSParams::GASolverParams::InitialSearchSpaceType::RANDOM);
//   io.enumCase(Space, "BEST10",
//               AOSParams::GASolverParams::InitialSearchSpaceType::BEST10);
//   io.enumCase(Space, "BASELINE",
//               AOSParams::GASolverParams::InitialSearchSpaceType::BASELINE);
// }

void MappingTraits<AOSParams::RMHCSolverParams>::mapping(
    IO &io, AOSParams::RMHCSolverParams &Params) {
  io.mapRequired("max", Params.Max);
  io.mapRequired("min", Params.Min);
  io.mapRequired("times", Params.Times);
  io.mapRequired("generations", Params.Generations);
  io.mapRequired("threshold", Params.Threshold);
}

void ScalarEnumerationTraits<AOSParams::MCStrategyType>::enumeration(
    IO &io, AOSParams::MCStrategyType &Param) {
  io.enumCase(Param, "CBR", AOSParams::MCStrategyType::CBR);
  io.enumCase(Param, "DPL", AOSParams::MCStrategyType::DPL);
  io.enumCase(Param, "RFL", AOSParams::MCStrategyType::RFL);
  io.enumCase(Param, "LTL", AOSParams::MCStrategyType::LTL);
}

void ScalarEnumerationTraits<AOSParams::CharacterizationStrategyType>::
    enumeration(IO &io, AOSParams::CharacterizationStrategyType &Param) {
  io.enumCase(Param, "DNA", AOSParams::CharacterizationStrategyType::DNA);
  io.enumCase(Param, "DND", AOSParams::CharacterizationStrategyType::DND);
  io.enumCase(Param, "FLL", AOSParams::CharacterizationStrategyType::FLL);
}

void ScalarEnumerationTraits<AOSParams::RetrieveStrategyType>::enumeration(
    IO &io, AOSParams::RetrieveStrategyType &Param) {
  io.enumCase(Param, "ELITE", AOSParams::RetrieveStrategyType::ELITE);
  io.enumCase(Param, "JUST", AOSParams::RetrieveStrategyType::JUST);
  io.enumCase(Param, "NEARLY", AOSParams::RetrieveStrategyType::NEARLY);
}

void ScalarEnumerationTraits<AOSParams::SimilarityStrategyType>::enumeration(
    IO &io, AOSParams::SimilarityStrategyType &Param) {
  io.enumCase(Param, "NaW", AOSParams::SimilarityStrategyType::NaW);
  io.enumCase(Param, "CMP", AOSParams::SimilarityStrategyType::CMP);
}