#pragma once

#include "AOSIROpt.hpp"
#include "AOSLog.hpp"
#include "CodeAnalyzer.hpp"
#include "AOSPasses.hpp"

#include <memory>

namespace dbt {

inline int getRandomNumber(int min, int max) { return (rand() % max) + min; }

inline float getRandomRate() {
  float r = getRandomNumber(0, 10);
  return (r /= 10);
}

class DNA {
protected:
  std::unique_ptr<AOSIROpt> IRO;
  std::unique_ptr<CodeAnalyzer> CA;
  std::vector<uint16_t> Genes;
  int Fitness;

public:
  DNA(std::vector<uint16_t> Genes) : Genes(std::move(Genes)) {
    IRO = llvm::make_unique<AOSIROpt>();
    CA = llvm::make_unique<CodeAnalyzer>();
  }

  DNA &operator=(const DNA &Other) noexcept {
    Genes = std::move(Other.Genes);
    Fitness = Other.Fitness;
    return *this;
  }

  inline const std::vector<uint16_t> &getGenes() const { return Genes; }
  void toPrintInfo(std::ofstream &File) const;
  void calcFitness(std::shared_ptr<llvm::Module> M);
  inline int getFitness() const { return Fitness; }
};


class GADNA : public DNA {
  float Probability;
public:
  GADNA(std::vector<uint16_t> Genes) : DNA(std::move(Genes)) {}

  void normalize(int);
  void mutate(float);
  GADNA* crossover(GADNA*, int);
  inline float getProbability() const { return Probability; }
  inline int getLocus(int index) const { return Genes[index]; }
  void toPrintInfo(std::ofstream &File) const;
};
} // namespace dbt
