#pragma once

#include "AOSIROpt.hpp"
#include "AOSLog.hpp"
#include "AOSPasses.hpp"
#include "CodeAnalyzer.hpp"

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
  std::vector<std::string> Genes;
  bool FitnessCalculated;
  double Fitness;

public:
  DNA(std::vector<std::string> Genes) : Genes(std::move(Genes)) {
    IRO = llvm::make_unique<AOSIROpt>();
    CA = llvm::make_unique<CodeAnalyzer>();
    FitnessCalculated = false;
  }

  DNA &operator=(const DNA &Other) noexcept {
    Genes = std::move(Other.Genes);
    Fitness = Other.Fitness;
    FitnessCalculated = Other.FitnessCalculated;
    return *this;
  }

  double getFitness(std::shared_ptr<llvm::Module> M);

  const std::vector<std::string> &getGenes() const { return Genes; }
  std::vector<std::string> getGenes() { return Genes; }

private:
  void calculateFitness(std::shared_ptr<llvm::Module> M);
};

// class GADNA : public DNA {
//   float Probability;

// public:
//   GADNA(std::vector<uint16_t> Genes) : DNA(std::move(Genes)) {}

//   void normalize(int);
//   void mutate(float);
//   GADNA *crossover(GADNA *, int);
//   inline float getProbability() const { return Probability; }
//   inline int getLocus(int index) const { return Genes[index]; }
//   void toPrintInfo(std::ofstream &File) const;
// };
} // namespace dbt
