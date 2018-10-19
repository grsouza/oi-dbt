#pragma once

#include <fstream>
#include <iostream>
#include <memory>

namespace dbt {
  class Population;
  class AOSLog {
    static std::fstream *File;
  public:
    AOSLog() {}
    void printPopulation(std::unique_ptr<Population> P);
  };
} //namespace dbt;
