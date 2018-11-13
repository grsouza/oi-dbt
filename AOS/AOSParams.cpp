#include "AOSParams.hpp"
#include "llvm/Support/YAMLTraits.h"

using namespace dbt;
using namespace llvm::yaml;

void MappingTraits<GASolverParams>::mapping(IO &io, GASolverParams &params) {
  io.mapRequired("generations", params.generations);
  io.mapRequired("mutationRate", params.mutationRate);
  io.mapRequired("populationSize", params.populationSize);
  io.mapRequired("searchSpace", params.searchSpace);
  io.mapRequired("max", params.max);
  io.mapRequired("min", params.min);
}

void MappingTraits<RMHCSolverParams>::mapping(IO &io,
                                              RMHCSolverParams &params) {
  io.mapRequired("generations", params.Generations);
  io.mapRequired("searchSpace", params.SearchSpace);
  io.mapRequired("min", params.Min);
  io.mapRequired("max", params.Max);
  io.mapRequired("size", params.Size);
}

void MappingTraits<AOSParams>::mapping(IO &io, AOSParams &params) {
  io.mapRequired("times", params.times);
  io.mapRequired("updateDatabase", params.updateDatabase);
  io.mapRequired("database", params.database);
  //   io.mapRequired("threshold", params.threshold);
  io.mapRequired("max", params.max);
  io.mapRequired("min", params.min);
  io.mapRequired("onlyOnce", params.onlyOnce);
  io.mapRequired("roi", params.roi);
  io.mapRequired("icStrategy", params.icStrategy.value);

  switch (params.icStrategy.value) {
  case AOSParams::ICStrategy::Value::GA:
    io.mapRequired("icStrategyParams", params.icStrategy.params.ga);
    break;
  case AOSParams::ICStrategy::Value::RMHC:
    io.mapRequired("icStrategyParams", params.icStrategy.params.rmhc);
    break;
  }

  io.mapRequired("retrieving", params.retrieve);
  // io.mapRequired("trainingPrograms", params.trainingPrograms);
  io.mapRequired("similarity", params.similarity);
  io.mapRequired("createDatabase", params.createDatabase);
  io.mapRequired("characterization", params.characterization);
  io.mapRequired("invokeIC", params.invokeIC);
  io.mapRequired("objective", params.objetive);
  io.mapRequired("report", params.report);
  io.mapRequired("training", params.training);
}

void ScalarEnumerationTraits<AOSParams::ICStrategy::Value>::enumeration(
    IO &io, AOSParams::ICStrategy::Value &strategy) {
  io.enumCase(strategy, "GA", AOSParams::ICStrategy::Value::GA);
  io.enumCase(strategy, "RMHC", AOSParams::ICStrategy::Value::RMHC);
}

void ScalarEnumerationTraits<AOSParams::RetrieveStrategy>::enumeration(
    IO &io, AOSParams::RetrieveStrategy &strategy) {
  io.enumCase(strategy, "ELITE", AOSParams::RetrieveStrategy::ELITE);
  io.enumCase(strategy, "JUST", AOSParams::RetrieveStrategy::JUST);
  io.enumCase(strategy, "NEARLY", AOSParams::RetrieveStrategy::NEARLY);
}

void ScalarEnumerationTraits<AOSParams::SimilarityStrategy>::enumeration(
    IO &io, AOSParams::SimilarityStrategy &strategy) {
  io.enumCase(strategy, "NaW", AOSParams::SimilarityStrategy::NAW);
  io.enumCase(strategy, "CMP", AOSParams::SimilarityStrategy::CMP);
}

void ScalarEnumerationTraits<AOSParams::CharacterizationStrategy>::enumeration(
    IO &io, AOSParams::CharacterizationStrategy &strategy) {
  io.enumCase(strategy, "DNA", AOSParams::CharacterizationStrategy::DNA);
  io.enumCase(strategy, "DND", AOSParams::CharacterizationStrategy::DND);
  io.enumCase(strategy, "FLL", AOSParams::CharacterizationStrategy::FLL);
}

void ScalarEnumerationTraits<AOSParams::Goal>::enumeration(
    IO &io, AOSParams::Goal &goal) {
  io.enumCase(goal, "runtime", AOSParams::Goal::RUNTIME);
  io.enumCase(goal, "size", AOSParams::Goal::SIZE);
  io.enumCase(goal, "energy", AOSParams::Goal::ENERGY);
}

void ScalarEnumerationTraits<AOSParams::Report>::enumeration(
    IO &io, AOSParams::Report &report) {
  io.enumCase(report, "SIMPLE", AOSParams::Report::SIMPLE);
  io.enumCase(report, "DETAILED", AOSParams::Report::DETAILED);
  io.enumCase(report, "NONE", AOSParams::Report::NONE);
}
