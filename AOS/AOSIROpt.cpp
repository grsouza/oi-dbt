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

const std::string AOSIROpt::opts[108] = {
      "aa-eval", "basicaa", "basiccg", "count-aa", "da", "debug-aa", "domfrontier", 
      "domtree", "dot-callgraph", "dot-cfg", "dot-cfg-only", "dot-dom", "dot-dom-only", "dot-postdom", 
      "dot-postdom-only", "globalsmodref-aa", "instcount", "intervals", "iv-users", "lazy-value-info", 
      "libcall-aa", "lint", "loops", "memdep", "module-debuginfo", "postdomfrontier", "postdomtree", 
      "print-alias-sets", "print-callgraph", "print-callgraph-sccs", "print-cfg-sccs", "print-dom-info", 
      "print-externalfnconstants", "print-function", "print-module", "print-used-types", "regions",
			"scalar-evolution", "scev-aa", "targetdata", "adce", "always-inline", "argpromotion", "bb-vectorize",
      "block-placement", "break-crit-edges", "codegenprepare", "constmerge", "constprop", "dce", "deadargelim", 
      "deadtypeelim", "die", "dse", "functionattrs", "globaldce", "globalopt", "gvn", "indvars", "inline", 
      "instcombine", "aggressive-instcombine", "internalize", "ipconstprop", "ipsccp", "jump-threading", "lcssa",
      "licm", "loop-deletion", "loop-extract", "loop-extract-single", "loop-reduce", "loop-rotate", 
      "loop-simplify", "loop-unroll", "loop-unroll-and-jam", "loop-unswitch", "loweratomic", "lowerinvoke", 
      "lowerswitch", "mem2reg", "memcpyopt", "mergefunc", "mergereturn", "partial-inliner", "prune-eh", 
      "reassociate", "reg2mem", "sroa", "sccp", "simplifycfg", "sink", "strip", "strip-dead-debug-info", 
      "strip-dead-prototypes", "strip-debug-declare", "strip-nondebug", "tailcallelim", "deadarghaX0r", 
      "extract-blocks", "instnamer", "verify", "view-cfg", "view-cfg-only", "view-dom", "view-dom-only", 
      "view-postdom", "view-postdom-only"};

constexpr unsigned int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

void dbt::AOSIROpt::populateFuncPassManager(llvm::legacy::FunctionPassManager* FPM, std::vector<std::string> PassesNames) {
  /*
  for (std::string PassName : PassesNames) {
    switch (str2int(PassName.c_str())) {
      case str2int("instcombine"):
        FPM->add(llvm::createInstructionCombiningPass());
        break;
      case str2int("simplifycfg"):
        FPM->add(llvm::createCFGSimplificationPass());
        break;
      case str2int("reassociate"):
        FPM->add(llvm::createReassociatePass());
        break;
      case str2int("gvn"):
        FPM->add(llvm::createNewGVNPass());
        break;
      case str2int("die"):
        FPM->add(llvm::createDeadInstEliminationPass());
        break;
      case str2int("dce"):
        FPM->add(llvm::createDeadCodeEliminationPass());
        break;
//      case str2int("mem2reg"):
//        FPM->add(llvm::createPromoteMemoryToRegisterPass());
//        break;
      case str2int("licm"):
        FPM->add(llvm::createLICMPass());
        break;
      case str2int("memcpyopt"):
        FPM->add(llvm::createMemCpyOptPass());
        break;
      case str2int("loop-unswitch"):
        FPM->add(llvm::createLoopUnswitchPass());
        break;
      case str2int("indvars"):
        FPM->add(llvm::createIndVarSimplifyPass());       // Canonicalize indvars
        break;
      case str2int("loop-deletion"):
        FPM->add(llvm::createLoopDeletionPass());         // Delete dead loops
        break;
      case str2int("loop-predication"):
        FPM->add(llvm::createLoopPredicationPass());
        break;
      case str2int("loop-unroll"):
        FPM->add(llvm::createSimpleLoopUnrollPass());     // Unroll small loops
        break;
      default:
        std::cerr << "Trying to use an invalid optimization pass!\n";
        exit(1);
        break;
    }
  }
  std::cerr << "\n";
*/
}

void dbt::AOSIROpt::customOptimizeIRFunction(llvm::Module* M, std::vector<std::string> Opts) {
  /*std::cerr << "Custom opt " << Opts[1] << "\n";
  auto PM = std::make_unique<llvm::legacy::FunctionPassManager>(M);
  populateFuncPassManager(PM.get(), Opts);
  PM->doInitialization();
  for (auto &F : *M)
    PM->run(F);*/
}

void dbt::AOSIROpt::optimizeIRFunction(llvm::Module *M, OptLevel Level) {
  // Lazy initialization
  /*
  if (Level == OptLevel::Basic) {
    if (!BasicPM) {
      BasicPM = std::make_unique<llvm::legacy::FunctionPassManager>(M);
      populateFuncPassManager(BasicPM.get(), 
        {"instcombine", "simplifycfg", "reassociate", "gvn", "die", "dce", "instcombine", "licm", 
        "memcpyopt", "loop-unswitch", "instcombine", "indvars", "loop-deletion", "loop-predication", "loop-unroll","simplifycfg", "instcombine", "licm", "gvn"});
      BasicPM->doInitialization();
    }
    for (auto &F : *M)
      BasicPM->run(F);
  } */
}
