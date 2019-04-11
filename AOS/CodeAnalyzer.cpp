#include "CodeAnalyzer.hpp"

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"

#include <cctype>
#include <chrono>
#include <ctime>
#include <iostream>

using namespace dbt;

static std::string exec(const char *cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);

  if (!pipe)
    throw std::runtime_error("popen() failed!");

  while (!feof(pipe.get())) {
    if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
      result += buffer.data();
  }

  return result;
}

double CodeAnalyzer::getIPC(std::shared_ptr<llvm::Module> M) {
  std::string MCAResult;
  std::string ipc = "";
  int k = 0;
  // llvm::Module to .bc file
  std::error_code EC;
  llvm::raw_fd_ostream OS("module.bc", EC, llvm::sys::fs::F_None);
  WriteBitcodeToFile(*M, OS);
  OS.flush();
  //.bc >> .s
  std::system("llc module.bc");
  // call llvm-mca
  MCAResult = exec("llvm-mca module.s");
  // find ipc
  for (int i = 0; i < MCAResult.size(); i++) {
    if (MCAResult[i] == 'I') {
      k = i + 4; // eat 'PC' and ':'
      if (k < MCAResult.size() && MCAResult[i + 1] == 'P' &&
          MCAResult[i + 2] == 'C') {
        while (MCAResult[k] == ' ')
          k++;
        while (std::isdigit(MCAResult[k]) || MCAResult[k] == '.') {
          ipc += MCAResult[k];
          k++;
        }
        break;
      }
    }
  }
  // remove module.bc and module.s
  // std::system("rm module.*");
  if (ipc.size() == 0) {
    std::cerr << "Problems with llvm-mca!\n";
    exit(1);
  }

  return strtod(ipc.c_str(), nullptr);
}
