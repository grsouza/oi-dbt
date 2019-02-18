#include "AOSLog.hpp"

using namespace dbt;

#include "GASolver.hpp"

void AOSLog::newRegion(int RegionID) {
  File.open(FileName, std::ostream::app);
  File << "--> REGION #" << RegionID << std::endl;
  File.close();
}

void AOSLog::population(std::shared_ptr<Population> P) {
  File.open(FileName, std::ostream::app);
  P->toPrintInfo(File);
  File << std::endl;
  File.close();
}

void AOSLog::dna(DNA *D) {
  File.open(FileName, std::ostream::app);
  D->toPrintInfo(File);
  File << std::endl;
  File.close();
}