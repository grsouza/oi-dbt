#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace dbt {
  class Population;
  class AOSLog {
    std::string FileName;
    std::ofstream File;
  public:
    AOSLog(const std::string &FileName) : FileName(FileName) {
      File.open(FileName); 
      File << "//===----------------------------------------------------------------------===//\n";
      File << "//// ADAPTATIVE SYSTEM OPTIMIZATIONS LOG #####" << std::endl; 
      File << "//===----------------------------------------------------------------------===//\n";
      File.close();
    }
    void newRegion(int); 
    void population(std::shared_ptr<Population>);
  };
} //namespace dbt;
