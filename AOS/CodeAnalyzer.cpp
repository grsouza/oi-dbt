#include <iostream>
#include "CodeAnalyzer.hpp"

using namespace dbt;

std::string exec(const char* cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
  if (!pipe) throw std::runtime_error("popen() failed!");
  while (!feof(pipe.get())) {
    if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
      result += buffer.data();
  }
  return result;
}

double CodeAnalyzer::getIPC(llvm::Module *M) {
  //std::error_code EC;
  //llvm::raw_fd_ostream OS("module.bc", EC, llvm::sys::fs::F_None);
  //llvm::WriteBitcodeToFile(*M, OS); 
  //std::cout << exec("llvm-mca-7 module.bc");
  return 0.0;
}
