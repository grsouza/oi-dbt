#ifndef IROpt_HPP
#define IROpt_HPP

#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include <AOS.hpp>

namespace dbt {
	class AOS;
  class IROpt {
    std::unique_ptr<llvm::legacy::FunctionPassManager> BasicPM;

    void populateFuncPassManager(llvm::legacy::FunctionPassManager*, std::vector<std::string>);
  public:
    IROpt() {}; 

    enum OptLevel { Basic, Soft, Medium, Hard, Custom };

    void optimizeIRFunction(llvm::Module*, OptLevel, dbt::AOS& A);
    void customOptimizeIRFunction(llvm::Module*, std::vector<std::string>);
  };
}

#endif
