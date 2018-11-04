#include "AOSIROpt.hpp"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/LinkAllPasses.h"
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

void dbt::AOSIROpt::populateFuncPassManager(llvm::legacy::FunctionPassManager* FPM, std::vector<uint16_t> Passes) {
  for (int PassIndex = 0; PassIndex < Passes.size(); PassIndex++) {
    switch (Passes[PassIndex]) { 
      case 1: //aa-eval
        FPM->add(llvm::createAAEvalPass());
        break;
      case 2: //dce
        FPM->add(llvm::createDeadCodeEliminationPass());
        break;
      case 3: //simplifycfg
        FPM->add(llvm::createCFGSimplificationPass());
        break;
      case 4: //reassociate
        FPM->add(llvm::createReassociatePass());
        break;
      case 5: //gvn
        FPM->add(llvm::createNewGVNPass());
        break;
      case 6: //die
        FPM->add(llvm::createDeadInstEliminationPass());
        break;
      case 7: //mem2reg
        FPM->add(llvm::createPromoteMemoryToRegisterPass());
        break;
      case 8: //licm
        FPM->add(llvm::createLICMPass());
        break;
      case 9: //memcpyopt
        FPM->add(llvm::createMemCpyOptPass());
        break;
      case 10: //loop-unswitch
        FPM->add(llvm::createLoopUnswitchPass());
        break;
      case 11: //indvars
        FPM->add(llvm::createIndVarSimplifyPass());       // Canonicalize indvars
        break;
      case 12: //loop-deletion
        FPM->add(llvm::createLoopDeletionPass());         // Delete dead loops
        break;
      case 13: //loop-predication
        FPM->add(llvm::createLoopPredicationPass());
        break;
      case 14: //loop-unroll
        FPM->add(llvm::createSimpleLoopUnrollPass());     // Unroll small loops
        break;
      case 15: //instcombine
        FPM->add(llvm::createInstructionCombiningPass());
        break;
      case 16: //always-inline
        FPM->add(llvm::createAlwaysInlinerLegacyPass());
        break;
      case 17: //dse
        FPM->add(llvm::createDeadStoreEliminationPass());
        break;
      case 18: //prune-eh
        FPM->add(llvm::createPruneEHPass());
        break;
      case 19: //adce
        FPM->add(llvm::createAggressiveDCEPass());
        break;
      case 20: //loop-idiom
        FPM->add(llvm::createLoopIdiomPass());
        break;
      case 21: //basicaa
        FPM->add(llvm::createBasicAAWrapperPass());
        break;
      case 22: //domtree
        FPM->add(llvm::createPostDomTree());
        break;
      case 23: //loop-rotate
        FPM->add(llvm::createLoopRotatePass());
        break;
      case 24: //globalopt
        FPM->add(llvm::createGlobalOptimizerPass());
        break;
      default:
        std::cerr << "Trying to use an invalid optimization pass!\n";
        exit(1);
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

void dbt::AOSIROpt::optimizeIRFunction(llvm::Module *M, std::vector<uint16_t> Opts, OptLevel Level) {
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
