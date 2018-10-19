#pragma once

#include <string>
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"

namespace dbt {
  #define OPTS_MIN_INDEX 0   //opts array minimum index
  #define OPTS_MAX_INDEX 107 //opts array maximum index

  class AOSIROpt {
    static const std::string opts[108]; 
    
    std::unique_ptr<llvm::legacy::FunctionPassManager> BasicPM;
    
    void populateFuncPassManager(llvm::legacy::FunctionPassManager*, std::vector<std::string>);
  public:
    AOSIROpt() {}; 

    enum OptLevel { Basic, Soft, Medium, Hard, Custom };

    void optimizeIRFunction(llvm::Module*, OptLevel);
    void customOptimizeIRFunction(llvm::Module*, std::vector<std::string>);
  };
} //namespace dbt
