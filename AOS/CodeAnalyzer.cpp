#include "CodeAnalyzer.hpp"

using namespace dbt;

std::string exec(const char *cmd) {
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

int CodeAnalyzer::getStaticSize(std::shared_ptr<llvm::Module> M) {
  int Size = 0;
  for (auto &F : *M)
    for (auto &BB : F)
      Size += BB.size();
  return Size;
}

int CodeAnalyzer::getDynamicSize(llvm::Module *M) {
  // like llvm-mca
}

double CodeAnalyzer::getIPC(llvm::Module *M) {
  std::string MCAResult;
  std::string ipc = "";
  int k = 0;
  // llvm::Module to .bc file
  std::error_code EC;
  llvm::raw_fd_ostream OS("module.bc", EC, llvm::sys::fs::F_None);
  WriteBitcodeToFile(*M, OS);
  OS.flush();
  //.bc >> .s
  std::system("llc-7 module.bc");
  // call llvm-mca
  MCAResult = exec("llvm-mca-7 module.s");
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
  std::system("rm module.*");
  if (ipc.size() == 0) {
    std::cerr << "Problems with llvm-mca!\n";
    exit(1);
  }
  return strtod(ipc.c_str(), nullptr);
  ;
}
