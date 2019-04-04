#include "AOSSimilarityStrategy.hpp"
#include "seqalign/needleman_wunsch.h"

using namespace dbt;

int NWAOSSimilarityStrategy::getSimilarityBetween(const std::string &A,
                                                  const std::string &B) {

  int result = 0;

  int match = 1, mismatch = -1, gap_open = -4, gap_extend = -1;

  bool no_start_gap_penalty = false, no_end_gap_penalty = false;
  bool no_gaps_in_a = true, no_gaps_in_b = true;
  bool no_mismatches = true, case_sensitive = true;

  scoring_t scoring;
  scoring_init(&scoring, match, mismatch, gap_open, gap_extend,
               no_start_gap_penalty, no_end_gap_penalty, no_gaps_in_a,
               no_gaps_in_b, no_mismatches, case_sensitive);

  nw_aligner_t *nw = needleman_wunsch_new();
  alignment_t *aln = alignment_create(256);

  needleman_wunsch_align(A.c_str(), B.c_str(), &scoring, nw, aln);

  result = aln->score;

  needleman_wunsch_free(nw);
  alignment_free(aln);

  return result;
}