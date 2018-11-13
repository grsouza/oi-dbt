#pragma once

#include "AOSIROpt.hpp"
#include "AOSLog.hpp"
#include "CodeAnalyzer.hpp"
#include <memory>

namespace dbt {

class DNA {
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

}; // namespace dbt