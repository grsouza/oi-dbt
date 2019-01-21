#include "AOSIROpt.hpp"
#include "llvm/Analysis/AliasAnalysis.h"
// #include "llvm/LinkAllPasses.h"
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

#include "AOSPasses.hpp"

using namespace dbt;

constexpr unsigned int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

void dbt::AOSIROpt::populateFuncPassManager(llvm::legacy::FunctionPassManager* FPM, std::vector<uint16_t> Passes) {
  for (int PassIndex = 0; PassIndex < Passes.size(); PassIndex++) {
    switch (Passes[PassIndex]) { 
      case DCE: //dce
        FPM->add(llvm::createDeadCodeEliminationPass());
        break;
      case SIMPLIFYCFG: //simplifycfg
        FPM->add(llvm::createCFGSimplificationPass());
        break;
      case REASSOCIATE: //reassociate
        FPM->add(llvm::createReassociatePass());
        break;
      case GVN: //gvn
        FPM->add(llvm::createNewGVNPass());
        break;
      case DIE: //die
        FPM->add(llvm::createDeadInstEliminationPass());
        break;
      case MEM2REG: //mem2reg
//        FPM->add(llvm::createPromoteMemoryToRegisterPass());
        break;
      case LICM: //licm
        FPM->add(llvm::createLICMPass());
        break;
      case MEMCPYOPT: //memcpyopt
        FPM->add(llvm::createMemCpyOptPass());
        break;
      case LOOP_UNSWITCH: //loop-unswitch
        FPM->add(llvm::createLoopUnswitchPass());
        break;
      case INDVARS: //indvars
        FPM->add(llvm::createIndVarSimplifyPass());
        break;
      case LOOP_DELETION: //loop-deletion
        FPM->add(llvm::createLoopDeletionPass());
        break;
      case LOOP_PREDICATION: //loop-predication
        FPM->add(llvm::createLoopPredicationPass());
        break;
      case LOOP_UNROLL: //loop-unroll
        FPM->add(llvm::createSimpleLoopUnrollPass());
        break;
      case INSTCOMBINE: //instcombine
//        FPM->add(llvm::createInstructionCombiningPass());
        break;
      case DSE: //dse
        FPM->add(llvm::createDeadStoreEliminationPass());
        break;
      case ADCE: //adce
        FPM->add(llvm::createAggressiveDCEPass());
        break;
      case LOOP_IDIOM: //loop-idiom
        FPM->add(llvm::createLoopIdiomPass());
        break;
      case BASICAA: //basicaa
//        FPM->add(llvm::createBasicAAWrapperPass());
        break;
      case DOMTREE: //domtree
//        FPM->add(llvm::createPostDomTree());
        break;
      case LOOP_ROTATE: //loop-rotate
        FPM->add(llvm::createLoopRotatePass());
        break;
      case _NONE:
        break;
      //case GLOBALOPT: //globalopt
      //  FPM->add(llvm::createGlobalOptimizerPass());
      //  break;
      //case PRUNE_EH: //prune-eh
      //  FPM->add(llvm::createPruneEHPass());
      //  break;
      //case ALWAYS_INLINE: //always-inline
      //  FPM->add(llvm::createAlwaysInlinerLegacyPass());
      //  break;
      //case AA_EVAL: //aa-eval
      //  FPM->add(llvm::createAAEvalPass());
      //  break;
      default:
        std::cerr << "Trying to use an invalid optimization pass!\n";
        exit(1);
        break;
    }
  }
}

void dbt::AOSIROpt::customOptimizeIRFunction(llvm::Module* M, std::vector<std::string> Opts) {
}

void dbt::AOSIROpt::optimizeIRFunction(std::shared_ptr<llvm::Module> M, std::vector<uint16_t> Opts, OptLevel Level) {
  llvm::Module *Mod = M.get();
  std::unique_ptr<llvm::legacy::FunctionPassManager> BPM;
  if (Level == OptLevel::Basic) {
    BPM = std::make_unique<llvm::legacy::FunctionPassManager>(Mod);
    populateFuncPassManager(BPM.get(), Opts);
    BPM->doInitialization();
    for (auto &F : *Mod) {
      BPM->run(F);
    }
  }
}
