#include "AOSLog.hpp"

using namespace dbt;

#include "GASolver.hpp"

void AOSLog::newRegion(int regionID) {
  File.open(FileName, std::ostream::app);
  File << "--> REGION #" << regionID  << std::endl;
  File.close();
}

void AOSLog::population(std::shared_ptr<Population> P) {
  File.open(FileName, std::ostream::app);
  P->toPrintInfo(File);
  File << std::endl;
  File.close();
}
