#pragma once

#include "AOSPasses.hpp"
#include <string>
#include <vector>

using namespace llvm::yaml;

namespace dbt {

static const std::vector<std::string> O3_PASSES = {
    // PASS_AA,
    PASS_ADCE,
    PASS_AGGRESSIVE_INSTCOMBINE,
    PASS_ALIGNMENT_FROM_ASSUMPTIONS,
    PASS_ARGPROMOTION,
    // PASS_ASSUMPTION_CACHE_TRACKER,
    PASS_BARRIER,
    PASS_BASICAA,
    // PASS_BASICCG,
    PASS_BDCE,
    // PASS_BLOCK_FREQ,
    // PASS_BRANCH_PROB,
    PASS_CALLED_VALUE_PROPAGATION,
    PASS_CALLSITE_SPLITTING,
    PASS_CONSTMERGE,
    PASS_CORRELATED_PROPAGATION,
    PASS_DEADARGELIM,
    // PASS_DEMANDED_BITS,
    PASS_DIV_REM_PAIRS,
    // PASS_DOMTREE,
    PASS_DSE,
    // PASS_EARLY_CSE_MEMSSA,
    PASS_ELIM_AVAIL_EXTERN,
    PASS_FLOAT2INT,
    // PASS_FORCEATTRS,
    // PASS_FUNCTIONATTRS,
    PASS_GLOBALDCE,
    PASS_GLOBALOPT,
    // PASS_GLOBALS_AA,
    PASS_GVN,
    PASS_INDVARS,
    // PASS_INFERATTRS,
    PASS_INLINE,
    PASS_INSTCOMBINE,
    PASS_INSTSIMPLIFY,
    PASS_IPSCCP,
    PASS_JUMP_THREADING,
    // PASS_LAZY_BLOCK_FREQ,
    // PASS_LAZY_BRANCH_PROB,
    PASS_LAZY_VALUE_INFO,
    PASS_LCSSA,
    // PASS_LCSSA_VERIFICATION,
    // PASS_LIBCALLS_SHRINKWRAP,
    PASS_LICM,
    // PASS_LOOP_ACCESSES,
    PASS_LOOP_DELETION,
    PASS_LOOP_DISTRIBUTE,
    PASS_LOOP_IDIOM,
    PASS_LOOP_LOAD_ELIM,
    PASS_LOOP_ROTATE,
    PASS_LOOP_SIMPLIFY,
    PASS_LOOP_SINK,
    PASS_LOOP_UNROLL,
    PASS_LOOP_UNSWITCH,
    PASS_LOOP_VECTORIZE,
    // PASS_LOOPS,
    PASS_MEM2REG,
    PASS_MEMCPYOPT,
    // PASS_MEMDEP,
    // PASS_MEMORYSSA,
    PASS_MLDST_MOTION,
    // PASS_OPT_REMARK_EMITTER,
    // PASS_PGO_MEMOP_OPT,
    // PASS_PHI_VALUES,
    // PASS_POSTDOMTREE,
    // PASS_PROFILE_SUMMARY_INFO,
    PASS_PRUNE_EH,
    PASS_REASSOCIATE,
    // PASS_RPO_FUNCTIONATTRS,
    // PASS_SCALAR_EVOLUTION,
    PASS_SCCP,
    // PASS_SCOPED_NOALIAS,
    PASS_SIMPLIFYCFG,
    PASS_SLP_VECTORIZER,
    PASS_SPECULATIVE_EXECUTION,
    PASS_SROA,
    PASS_STRIP_DEAD_PROTOTYPES,
    PASS_TAILCALLELIM,
    // PASS_TARGETLIBINFO,
    // PASS_TBAA,
    // PASS_TTI,
    // PASS_VERIFY,
};

} // namespace dbt