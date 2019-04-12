#include <AOSIROpt.hpp>
#include <OIPrinter.hpp>
#include <manager.hpp>

// Opt
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/Passes.h"

#include "llvm/Transforms/AggressiveInstCombine/AggressiveInstCombine.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Scalar/InstSimplifyPass.h"
#include "llvm/Transforms/Scalar/Scalarizer.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Vectorize.h"

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Bitcode/BitcodeWriterPass.h"

#include "llvm/CodeGen/Passes.h"

#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/LegacyPassManagers.h"
#include "llvm/IR/Verifier.h"

#include "llvm/Support/raw_ostream.h"

#include "timer.hpp"

constexpr unsigned int str2int(const char *str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

/*
 * BEST-10
 *
 * basicaa
 * codegenprepare
 * constmerge
 * early-cse
 * globalopt
 * gvn
 * instcombine
 * internalize
 * inline
 * indvars
 * ipsccp
 * licm
 * loop-instsimplify
 * loop-reduce
 * loop-idiom
 * loop-deletion
 * loop-rotate
 * loop-unroll
 * partial-inliner
 * reassociate
 * simplifycfg
 * tailcallelim
 *
 */

/*
 * Pass 'CodeGen Prepare' is not initialized.
 * Verify if there is a pass dependency cycle.
 * Required Passes:
 *       Profile summary info
 *       Target Library Information
 */

/*
 * Internalize
 *
 * Module->getFunction has returned empty!
 *
 */

/*
 * BEST-10 - não existe mais
 *
 * unroll-allow-partial
 * simplify-libcalls (habilitada por padrão - hoje tem
 * disable-simplify-libcalls) scalarrepl
 *
 */

/*
 * BEST-10
 *
 *
 * [-instcombine, -simplifycfg, -gvn, -indvars, -loop-rotate,
 * -unroll-allow-partial, -loop-unroll, -loop-rotate, -loop-unroll, -gvn,
 * -inline, -early-cse, -basicaa, -reassociate, -instcombine]
 * [-simplify-libcalls, -simplifycfg, -unroll-allow-partial, -internalize, -gvn,
 * -instcombine, -inline, -globalopt, -scalarrepl, -loop-rotate, -loop-unroll,
 * -loop-instsimplify]
 * [-gvn, -loop-rotate, -internalize, -inline, -licm, -tailcallelim,
 * -instcombine, -basicaa, -indvars]
 * [-codegenprepare, -loop-rotate, -loop-idiom, -loop-deletion, -gvn]
 * [-loop-rotate, -inline, -simplify-libcalls, -basicaa, -licm, -constmerge,
 * -indvars, -unroll-allow-partial, -loop-unroll, -reassociate, -gvn]
 * [-simplifycfg, -tailcallelim, -early-cse, -loop-rotate, -internalize,
 * -partial-inliner, -instcombine, -inline, -ipsccp]
 * [-internalize, -inline, -globalopt, -early-cse, -licm, -basicaa, -indvars,
 * -loop-reduce]
 * [-codegenprepare, -gvn, -tailcallelim, -reassociate, -basicaa, -inline,
 * -loop-rotate, -indvars, -reassociate]
 * [-simplifycfg, -tailcallelim, -instcombine, -early-cse]
 * [-early-cse, -simplifycfg, -gvn, -inline, -loop-reduce, -licm, -instcombine,
 * -gvn, -reassociate]
 *
 */

/*
 * O3
 *
 * aa adce aggressive-instcombine alignment-from-assumptions argpromotion
 * assumption-cache-tracker barrier basicaa basiccg bdce block-freq branch-prob
 * called-value-propagation callsite-splitting constmerge correlated-propagation
 * deadargelim demanded-bits div-rem-pairs domtree dse early-cse-memssa
 * elim-avail-extern float2int forceattrs functionattrs globaldce globalopt
 * globals-aa gvn indvars inferattrs inline instcombine instsimplify ipsccp
 * jump-threading lazy-block-freq lazy-branch-prob lazy-value-info lcssa
 * lcssa-verification libcalls-shrinkwrap licm loop-accesses loop-deletion
 * loop-distribute loop-idiom loop-load-elim loop-rotate loop-simplify loop-sink
 * loop-unroll loop-unswitch loop-vectorize loops mem2reg memcpyopt memdep
 * memoryssa mldst-motion opt-remark-emitter pgo-memop-opt phi-values
 * postdomtree profile-summary-info prune-eh reassociate rpo-functionattrs
 * scalar-evolution sccp scoped-noalias simplifycfg slp-vectorizer
 * speculative-execution sroa strip-dead-prototypes tailcallelim targetlibinfo
 * tbaa tti verify
 */

/*
 * Falta adicionar para O3
 *
 * aa assumption-cache-tracker basiccg block-freq branch-prob demanded-bits
 * domtree early-cse-memssa forceattrs functionattrs globals-aa inferattrs
 * lazy-block-freq lazy-branch-prob lcssa-verification libcalls-shrinkwrap
 * loop-accesses loops memdep memoryssa opt-remark-emitter pgo-memop-opt
 * phi-values postdomtree profile-summary-inf rpo-functionattrs scalar-evolution
 * scoped-noalias targetlibinfo tbaa tti verify
 *
 */

void dbt::AOSIROpt::populatePassManager(llvm::legacy::PassManager *MPM,
                                        llvm::legacy::FunctionPassManager *FPM,
                                        std::vector<std::string> PassesNames) {
  for (std::string PassName : PassesNames) {
    switch (str2int(PassName.c_str())) {

    /*
     * Module Pass
     */

    /*
     * Scalar Transformations (Transform/Scalar.h)
     */
    case str2int("-rewrite-statepoints-for-gc"): // Make relocations explicit at
      // statepoints
      MPM->add(llvm::createRewriteStatepointsForGCLegacyPass());
      break;

      /*
       * Interprocedural Transformations (Transform/IPO.h)
       */
    case str2int("-strip"): // Strip all symbols from a module
      MPM->add(llvm::createStripSymbolsPass());
      break;
    case str2int("-strip-nondebug"): // Strip all symbols, except dbg symbols,
      // from a module
      MPM->add(llvm::createStripNonDebugSymbolsPass());
      break;
    case str2int(
        "-strip-debug-declare"): // Strip all llvm.dbg.declare intrinsics
      MPM->add(llvm::createStripDebugDeclarePass());
      break;
    case str2int(
        "-strip-dead-debug-info"): // Strip debug info for unused symbols
      MPM->add(llvm::createStripDeadDebugInfoPass());
      break;
    case str2int("-constmerge"): // Merge Duplicate Global Constants
      MPM->add(llvm::createConstantMergePass());
      break;
    case str2int("-globalopt"): // Global Variable Optimizer
      MPM->add(llvm::createGlobalOptimizerPass());
      break;
    case str2int("-globaldce"): // Dead Global Elimination
      MPM->add(llvm::createGlobalDCEPass());
      break;
    case str2int(
        "-elim-avail-extern"): // Eliminate Available Externally Globals
      MPM->add(llvm::createEliminateAvailableExternallyPass());
      break;
    case str2int("-inline"): // Function Integration/Inlining
      MPM->add(llvm::createFunctionInliningPass());
      break;
    case str2int("-prune-eh"): // Remove unused exception handling info
      MPM->add(llvm::createPruneEHPass());
      break;
    case str2int("-internalize"): // Internalize Global Symbols
      MPM->add(llvm::createInternalizePass());
      break;
    case str2int("-deadargelim"): // Dead Argument Elimination
      MPM->add(llvm::createDeadArgEliminationPass());
      break;
    case str2int(
        "-argpromotion"): // Promote 'by reference' arguments to scalars
      MPM->add(llvm::createArgumentPromotionPass());
      break;
    case str2int("-ipconstprop"): // Interprocedural constant propagation
      MPM->add(llvm::createIPConstantPropagationPass());
      break;
    case str2int(
        "-ipsccp"): // Interprocedural Sparse Conditional Constant Propagation
      MPM->add(llvm::createIPSCCPPass());
      break;
    case str2int("-loop-extract"): // Extract loops into new functions
      MPM->add(llvm::createLoopExtractorPass());
      break;
    case str2int(
        "-loop-extract-single"): // Extract at most one loop into a new function
      MPM->add(llvm::createSingleLoopExtractorPass());
      break;
    case str2int("-extract-blocks"): // Extract basic blocks from module
      MPM->add(llvm::createBlockExtractorPass());
      break;
    case str2int("-strip-dead-prototypes"): // Strip Unused Function Prototypes
      MPM->add(llvm::createStripDeadPrototypesPass());
      break;
    case str2int("-mergefunc"): // Merge Functions
      MPM->add(llvm::createMergeFunctionsPass());
      break;
    case str2int("-partial-inliner"): // Partial Inliner
      MPM->add(llvm::createPartialInliningPass());
      break;
    case str2int("-barrier"): // A No-Op Barrier Pass
      MPM->add(llvm::createBarrierNoopPass());
      break;
    case str2int("-called-value-propagation"): // Called Value Propagation
      MPM->add(llvm::createCalledValuePropagationPass());
      break;
    case str2int("-cross-dso-cfi"): // Cross-DSO CFI
      MPM->add(llvm::createCrossDSOCFIPass());
      break;
    case str2int("-globalsplit"): // Global splitter
      MPM->add(llvm::createGlobalSplitPass());
      break;

      /*
       * (Transforms/Utils.h)
       */
    case str2int("-metarenamer"): // Assign new names to everything
      MPM->add(llvm::createMetaRenamerPass());
      break;

      /*
       * Function Pass
       */

      /*
       * Scalar Transformations (Transform/Scalar.h)
       */
    case str2int("-constprop"): // Simple constant propagation
      FPM->add(llvm::createConstantPropagationPass());
      break;
    case str2int("-alignment-from-assumptions"): // Alignment from assumptions
      FPM->add(llvm::createAlignmentFromAssumptionsPass());
      break;
    case str2int("-sccp"): // Sparse Conditional Constant Propagation
      FPM->add(llvm::createSCCPPass());
      break;
    case str2int("-die"): // Dead Instruction Elimination
      FPM->add(llvm::createDeadInstEliminationPass());
      break;
    case str2int("-dce"): // Dead Code Elimination
      FPM->add(llvm::createDeadCodeEliminationPass());
      break;
    case str2int("-dse"): // Dead Store Elimination
      FPM->add(llvm::createDeadStoreEliminationPass());
      break;
    case str2int("-callsite-splitting"): // Call-site splitting
      FPM->add(llvm::createCallSiteSplittingPass());
      break;
    case str2int("-adce"): // Aggressive Dead Code Elimination
      FPM->add(llvm::createAggressiveDCEPass());
      break;
    case str2int("-guard-widening"): // Widen guards
      FPM->add(llvm::createGuardWideningPass());
      break;
    case str2int("-loop-guard-widening"): // Widen guards (within a single loop,
      // as a loop pass)
      FPM->add(llvm::createLoopGuardWideningPass());
      break;
    case str2int("-bdce"): // Bit-Tracking Dead Code Elimination
      FPM->add(llvm::createBitTrackingDCEPass());
      break;
    case str2int("-sroa"): // Scalar Replacement Of Aggregates
      FPM->add(llvm::createSROAPass());
      break;
    case str2int("-irce"): // Inductive range check elimination
      FPM->add(llvm::createInductiveRangeCheckEliminationPass());
      break;
    case str2int("-indvars"): // Induction Variable Simplification
      FPM->add(llvm::createIndVarSimplifyPass());
      break;
    case str2int("-licm"): // Loop Invariant Code Motion
      FPM->add(llvm::createLICMPass());
      break;
    case str2int("-loop-sink"): // Loop sink
      FPM->add(llvm::createLoopSinkPass());
      break;
    case str2int("-loop-predication"): // Loop prediction
      FPM->add(llvm::createLoopPredicationPass());
      break;
    case str2int("-loop-interchange"): // Loop interchange
      FPM->add(llvm::createLoopInterchangePass());
      break;
    case str2int("-loop-reduce"): // Loop Strength Reduction
      FPM->add(llvm::createLoopStrengthReducePass());
      break;
    case str2int("-loop-unswitch"): // Unswitch loops
      FPM->add(llvm::createLoopUnswitchPass());
      break;
    case str2int("-loop-instsimplify"): // Simplify instructions in loops
      FPM->add(llvm::createLoopInstSimplifyPass());
      break;
    case str2int("-loop-unroll"): // Unroll loops
      FPM->add(llvm::createSimpleLoopUnrollPass());
      break;
    case str2int("-loop-unroll-and-jam"): //  Unroll and Jam loops
      FPM->add(llvm::createLoopUnrollAndJamPass());
      break;
    case str2int("-loop-reroll"): // Reroll loops
      FPM->add(llvm::createLoopRerollPass());
      break;
    case str2int("-loop-rotate"): // Rotate Loops
      FPM->add(llvm::createLoopRotatePass());
      break;
    case str2int("-loop-idiom"): // Recognize loop idioms
      FPM->add(llvm::createLoopIdiomPass());
      break;
    case str2int("-loop-versioning-licm"): // Loop Versioning For LICM
      FPM->add(llvm::createLoopVersioningLICMPass());
      break;
    case str2int("-reassociate"): // Reassociate expressions
      FPM->add(llvm::createReassociatePass());
      break;
    case str2int("-jump-threading"): // Jump Threading
      FPM->add(llvm::createJumpThreadingPass());
      break;
    case str2int("-simplifycfg"): // Simplify the CFG
      FPM->add(llvm::createCFGSimplificationPass());
      break;
    case str2int("-flattencfg"): // Flatten the CFG
      FPM->add(llvm::createFlattenCFGPass());
      break;
    case str2int("-structurizecfg"): // Structurize the CFG
      FPM->add(llvm::createStructurizeCFGPass());
      break;
    case str2int("-tailcallelim"): // Tail Call Elimination
      FPM->add(llvm::createTailCallEliminationPass());
      break;
    case str2int("-early-cse"): // Early CSE
      FPM->add(llvm::createEarlyCSEPass());
      break;
    case str2int("-gvn-hoist"): // Early GVN Hoisting of Expressions
      FPM->add(llvm::createGVNHoistPass());
      break;
    case str2int("-gvn-sink"): // Early GVN sinking of Expressions
      FPM->add(llvm::createGVNSinkPass());
      break;
    case str2int("-mldst-motion"): // MergedLoadStoreMotion
      FPM->add(llvm::createMergedLoadStoreMotionPass());
      break;
    case str2int("-newgvn"): //  Global Value Numbering
      FPM->add(llvm::createNewGVNPass());
      break;
    case str2int(
        "-div-rem-pairs"): // Hoist/decompose integer division and remainder
      FPM->add(llvm::createDivRemPairsPass());
      break;
    case str2int("-memcpyopt"): // MemCpy Optimization
      FPM->add(llvm::createMemCpyOptPass());
      break;
    case str2int("-loop-deletion"): // Delete dead loops
      FPM->add(llvm::createLoopDeletionPass());
      break;
    case str2int("-consthoist"): // Constant Hoisting
      FPM->add(llvm::createConstantHoistingPass());
      break;
    case str2int("-sink"): // Code sinking
      FPM->add(llvm::createSinkingPass());
      break;
    case str2int("-loweratomic"): // Lower atomic intrinsics to non-atomic form
      FPM->add(llvm::createLowerAtomicPass());
      break;
    case str2int("-lower-guard-intrinsic"): // Lower the guard intrinsic to
      // normal control flow
      FPM->add(llvm::createLowerGuardIntrinsicPass());
      break;
    case str2int("-mergeicmps"): // Merge contiguous icmps into a memcmp
      FPM->add(llvm::createMergeICmpsPass());
      break;
    case str2int("-correlated-propagation"): // Value Propagation
      FPM->add(llvm::createCorrelatedValuePropagationPass());
      break;
    case str2int("-infer-address-spaces"): //
      FPM->add(llvm::createInferAddressSpacesPass());
      break;
    case str2int("-lower-expect"): // Lower 'expect' Intrinsics
      FPM->add(llvm::createLowerExpectIntrinsicPass());
      break;
    case str2int("-partially-inline-libcalls"): // Partially inline calls to
      // library functions
      FPM->add(llvm::createPartiallyInlineLibCallsPass());
      break;
    case str2int("-scalarizer"): // Scalarize vector operations
      FPM->add(llvm::createScalarizerPass());
      break;
    case str2int(
        "-separate-const-offset-from-gep"): // Split GEPs to a variadic base and
      // a constant offset for better CSE
      FPM->add(llvm::createSeparateConstOffsetFromGEPPass());
      break;
    case str2int(
        "-speculative-execution"): // Speculatively execute instructions
      FPM->add(llvm::createSpeculativeExecutionPass());
      break;
    case str2int("-slsr"): // Straight line strength reduction
      FPM->add(llvm::createStraightLineStrengthReducePass());
      break;
    case str2int("-place-safepoints"): // Place Safepoints
      FPM->add(llvm::createPlaceSafepointsPass());
      break;
    case str2int("-float2int"): // Float to int
      FPM->add(llvm::createFloat2IntPass());
      break;
    case str2int("-nary-reassociate"): // Nary reassociation
      FPM->add(llvm::createNaryReassociatePass());
      break;
    case str2int("-loop-distribute"): // Loop Distribution
      FPM->add(llvm::createLoopDistributePass());
      break;
    case str2int("-loop-load-elim"): // Loop Load Elimination
      FPM->add(llvm::createLoopLoadEliminationPass());
      break;
    case str2int("-loop-versioning"): // Loop Versioning
      FPM->add(llvm::createLoopVersioningPass());
      break;
    case str2int("-loop-data-prefetch"): // Loop Data Prefetch
      FPM->add(llvm::createLoopDataPrefetchPass());
      break;

      /*
       * (Transforms/Scalar/GVN.h)
       */
    case str2int("-gvn"): // Global Value Numbering
      FPM->add(llvm::createGVNPass());
      break;

      /*
       * (Transforms/Scalar/InstSimplifyPass.h)
       */
    case str2int("-instsimplify"): // Remove redundant instructions
      FPM->add(llvm::createInstSimplifyLegacyPass());
      break;

      /*
       * (Transforms/InstCombine/InstCombine.h)
       */
    case str2int("-instcombine"): // Combine redundant instructions
      FPM->add(llvm::createInstructionCombiningPass());
      break;

      /*
       * (Transforms/AggressiveInstCombine/AggressiveInstCombine.h)
       */
    case str2int(
        "-aggressive-instcombine"): // Combine pattern based expressions
      FPM->add(llvm::createAggressiveInstCombinerPass());
      break;

      /*
       * (Transforms/Utils.h)
       */
    case str2int("-lowerinvoke"): // Lower invoke and unwind, for unwindless
      // code generators
      FPM->add(llvm::createLowerInvokePass());
      break;
    case str2int("-instnamer"): // Assign names to anonymous instructions
      FPM->add(llvm::createInstructionNamerPass());
      break;
    case str2int("-lowerswitch"): // Lower SwitchInst's to branches
      FPM->add(llvm::createLowerSwitchPass());
      break;
    case str2int("-break-crit-edges"): // Break critical edges in CFG
      FPM->add(llvm::createBreakCriticalEdgesPass());
      break;
    case str2int("-lcssa"): // Loop-Closed SSA Form Pass
      FPM->add(llvm::createLCSSAPass());
      break;
    case str2int("-mem2reg"): // Promote Memory to Register
      FPM->add(llvm::createPromoteMemoryToRegisterPass());
      break;
    case str2int("-loop-simplify"): // Simplify loop CFG
      FPM->add(llvm::createLoopSimplifyPass());
      break;

      /*
       * (CodeGen/Passes.h)
       */
    case str2int("-codegenprepare"): // Optimize for code generation
      FPM->add(llvm::createCodeGenPreparePass());
      break;

      /*
       * (Transforms/Vectorize.h)
       */
    case str2int("-loop-vectorize"): // Loop Vectorization
      FPM->add(llvm::createLoopVectorizePass());
      break;
    case str2int("-slp-vectorizer"): // SLP Vectorizer
      FPM->add(llvm::createSLPVectorizerPass());
      break;
    case str2int(
        "-load-store-vectorizer"): // Vectorize load and store instructions
      FPM->add(llvm::createLoadStoreVectorizerPass());
      break;

      /*
       * Analyses (Analysis/Passes.h)
       */
    case str2int("-pa-eval"): // Evaluate ProvenanceAnalysis on all pairs
      FPM->add(llvm::createPAEvalPass());
      break;
    case str2int("-lazy-value-info"): // Lazy Value Information Analysis
      FPM->add(llvm::createLazyValueInfoPass());
      break;
    case str2int("-da"): // Dependence Analysis ??????
      FPM->add(llvm::createDependenceAnalysisWrapperPass());
      break;
    case str2int("-cost-model"): // Cost Model Analysis
      FPM->add(llvm::createCostModelAnalysisPass());
      break;
    case str2int("-delinearize"): // Delinearization
      FPM->add(llvm::createDelinearizationPass());
      break;
    case str2int("-divergence"): // Divergence Analysis
      FPM->add(llvm::createLegacyDivergenceAnalysisPass());
      break;
    case str2int("-instcount"): // Counts the various types of Instructions
      FPM->add(llvm::createInstCountPass());
      break;
    case str2int("-regions"): // Detect single entry single exit regions
      FPM->add(llvm::createRegionInfoPass());
      break;

      /*
       * Analyses (Analysis/BasicAliasAnalysis.h)
       */
    case str2int("-basicaa"): // Evaluate ProvenanceAnalysis on all pairs ????
      FPM->add(llvm::createBasicAAWrapperPass());
      break;

    default:
      std::cerr << "Trying to use an invalid optimization pass ("
                << PassName.c_str() << ")\n";
      exit(1);
      break;
    }
  }
  // std::cerr << "\n";
}

void dbt::AOSIROpt::customOptimizeIRFunction(llvm::Module *M,
                                             std::vector<std::string> Opts) {
  /*std::cerr << "Custom opt: " ;
    for (std::string Opt : Opts)
    std::cerr << Opt << " ";
    std::cerr << "\n";*/

  auto FPM = std::make_unique<llvm::legacy::FunctionPassManager>(M);
  auto MPM = std::make_unique<llvm::legacy::PassManager>();

  MPM->run(*M);

  populatePassManager(MPM.get(), FPM.get(), Opts);

  MPM->run(*M);

  FPM->doInitialization();
  for (auto &F : *M)
    FPM->run(F);
}

void dbt::AOSIROpt::optimizeIRFunction(llvm::Module *M, OptLevel Level) {
  // Lazy initialization
  // std::cerr << "Basic opt " << "\n";
  if (Level == OptLevel::Basic) {
    if (!BasicFPM) {
      BasicMPM = std::make_unique<llvm::legacy::PassManager>();
      BasicFPM = std::make_unique<llvm::legacy::FunctionPassManager>(M);
      populatePassManager(BasicMPM.get(), BasicFPM.get(),
                          {"-ipsccp",
                           "-inline",
                           "-partial-inliner",
                           "-instcombine",
                           "-simplifycfg",
                           "-reassociate",
                           "-gvn",
                           "-die",
                           "-dce",
                           "-instcombine",
                           "-licm",
                           "-memcpyopt",
                           "-loop-unswitch",
                           "-instcombine",
                           "-indvars",
                           "-loop-deletion",
                           "-loop-predication",
                           "-loop-unroll",
                           "-simplifycfg",
                           "-instcombine",
                           "-licm",
                           "-gvn"});

      BasicFPM->doInitialization();
    }

    BasicMPM->run(*M);

    for (auto &F : *M)
      BasicFPM->run(F);
  }
}
