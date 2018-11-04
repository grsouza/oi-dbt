#pragma once

#include <string>
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"

#define OPT_MIN 1 
#define OPT_MAX 6 
  
namespace dbt {
  class AOSIROpt {
    std::unique_ptr<llvm::legacy::FunctionPassManager> BasicPM;
    
    void populateFuncPassManager(llvm::legacy::FunctionPassManager*, std::vector<uint16_t>);
  public:
    AOSIROpt() {}; 

    enum OptLevel { Basic, Soft, Medium, Hard, Custom };

    void optimizeIRFunction(llvm::Module*, std::vector<uint16_t>, OptLevel);
    void customOptimizeIRFunction(llvm::Module*, std::vector<std::string>);
  };
} //namespace dbt
