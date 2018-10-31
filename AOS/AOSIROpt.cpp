#include "AOSIROpt.hpp"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Bitcode/BitcodeWriterPass.h"
#include "llvm/IR/LegacyPassManagers.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "timer.hpp"

using namespace dbt;

constexpr unsigned int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

void dbt::AOSIROpt::populateFuncPassManager(llvm::legacy::FunctionPassManager* FPM, std::vector<int> Passes) {
  for (int PassIndex = 0; PassIndex < Passes.size(); PassIndex++) {
    switch (Passes[PassIndex]) {
      case 0:
        FPM->add(llvm::createInstructionCombiningPass());
        break;
      case 1:
        FPM->add(llvm::createCFGSimplificationPass());
        break;
      case 2:
        FPM->add(llvm::createReassociatePass());
        break;
      case 3:
        FPM->add(llvm::createNewGVNPass());
        break;
      case 4:
        FPM->add(llvm::createDeadInstEliminationPass());
        break;
      case 5:
        FPM->add(llvm::createDeadCodeEliminationPass());
        break;
//      case str2int("mem2reg"):
//        FPM->add(llvm::createPromoteMemoryToRegisterPass());
//        break;
      case 6:
        FPM->add(llvm::createLICMPass());
        break;
      case 7:
        FPM->add(llvm::createMemCpyOptPass());
        break;
      case 8:
        FPM->add(llvm::createLoopUnswitchPass());
        break;
      case 9:
        FPM->add(llvm::createIndVarSimplifyPass());       // Canonicalize indvars
        break;
      case 10:
        FPM->add(llvm::createLoopDeletionPass());         // Delete dead loops
        break;
      case 11:
        FPM->add(llvm::createLoopPredicationPass());
        break;
      case 12:
        FPM->add(llvm::createSimpleLoopUnrollPass());     // Unroll small loops
        break;
      default:
        //std::cerr << "Trying to use an invalid optimization pass!\n";
        //exit(1);
        break;
    }
  }
  std::cerr << "\n";
}

void dbt::AOSIROpt::customOptimizeIRFunction(llvm::Module* M, std::vector<std::string> Opts) {
  /*std::cerr << "Custom opt " << Opts[1] << "\n";
  auto PM = std::make_unique<llvm::legacy::FunctionPassManager>(M);
  populateFuncPassManager(PM.get(), Opts);
  PM->doInitialization();
  for (auto &F : *M)
    PM->run(F);*/
}

void dbt::AOSIROpt::optimizeIRFunction(llvm::Module *M, OptLevel Level, std::vector<int> Opts) {
  // Lazy initialization
  if (Level == OptLevel::Basic) {
    if (!BasicPM) {
      BasicPM = std::make_unique<llvm::legacy::FunctionPassManager>(M);
      populateFuncPassManager(BasicPM.get(), Opts);
      BasicPM->doInitialization();
    }
    for (auto &F : *M)
      BasicPM->run(F);
  }
}
