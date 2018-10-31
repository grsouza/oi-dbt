#include "AOSLog.hpp"

using namespace dbt;

std::fstream* AOSLog::File = new std::fstream("Log.out");

void AOSLog::printPopulation(std::unique_ptr<Population> P) {
  std::cout << "POP\n";  
}
