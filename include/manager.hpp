#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <AOS.hpp>
#include <IREmitter.hpp>
#include <IRJIT.hpp>
#include <OIPrinter.hpp>
#include <chrono>
#include <machine.hpp>
#include <mutex>
#include <shared_mutex>
#include <sparsepp/spp.h>
#include <stack>
#include <thread>
#include <timer.hpp>
#include <unistd.h>

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/TargetSelect.h"

#ifndef OIInstList
#define OIInstList std::vector<std::array<uint32_t, 2>>
#endif

#define NATIVE_REGION_SIZE 1000000

namespace dbt {
struct ROIInfo {
  unsigned RegionID;
  std::vector<std::string> Opts;
};
class IREmitter;
class Machine;
class AOS;
class Manager {
public:
  enum OptPolitic { None, Normal, Aggressive, Custom };

private:
  llvm::LLVMContext TheContext;
  dbt::Machine &TheMachine;
  dbt::AOS &TheAOS;
  std::string RegionPath;

  ROIInfo ROI;

  std::vector<uint32_t> OIRegionsKey;
  spp::sparse_hash_map<uint32_t, OIInstList> OIRegions;
  std::mutex NR;
  std::condition_variable cv;
  std::atomic<size_t> NumOfOIRegions;
  std::unordered_map<uint32_t, OIInstList> CompiledOIRegions;
  std::vector<uint32_t> IRRegionsKey;
  std::set<uint32_t> TouchedEntries;
  spp::sparse_hash_map<uint32_t, llvm::Module *> IRRegions;
  volatile uint64_t NativeRegions[NATIVE_REGION_SIZE];

  mutable std::shared_mutex OIRegionsMtx, IRRegionsMtx, NativeRegionsMtx,
      CompiledOIRegionsMtx;

  OptPolitic OptMode;
  std::unordered_map<uint32_t, std::vector<std::string>> *CustomOpts;

  std::vector<OIInstList> OIFuncs;
  std::vector<std::vector<uint32_t>> OIFuncsEntries;
  uint32_t NumFuncs = 0;

  uint32_t DataMemOffset;

  std::unique_ptr<IREmitter> IRE;
  std::unique_ptr<llvm::orc::IRJIT> IRJIT;

  std::atomic<bool> isRegionRecorging;
  std::atomic<bool> isRunning;
  std::atomic<bool> isFinished;
  std::vector<std::thread> ThreadPool;

  unsigned regionFrequency = 0;
  unsigned CompiledRegions = 0;
  unsigned OICompiled = 0;
  unsigned LLVMCompiled = 0;
  float AvgOptCodeSize = 0;

  bool VerboseOutput = false;
  bool LockMode = false;
  bool ROIMode = false;

  std::unordered_map<uint32_t, llvm::Module *> ModulesLoaded;
  bool IsToLoadRegions = false;
  bool IsToDoWholeCompilation = false;
  bool IsToLoadBCFormat = true;
  bool IsToInline = false;

  llvm::Module *loadRegionFromFile(std::string);
  void loadRegionsFromFiles();

  void inlineCall(uint32_t, uint32_t, OIInstList &, std::set<uint32_t> &,
                  llvm::Module *);

  void runPipeline();
  std::ofstream *PerfMapFile;

public:
  Manager(uint32_t DMO, dbt::Machine &M, dbt::AOS &A, bool VO = false,
          bool Inline = false)
      : DataMemOffset(DMO), isRunning(true), isFinished(false),
        VerboseOutput(VO), TheMachine(M), TheAOS(A), NumOfOIRegions(0),
        IsToInline(Inline) {
    memset((void *)NativeRegions, 0, sizeof(NativeRegions));
  }

  void startCompilationThr() {
    if (IsToLoadRegions)
      loadRegionsFromFiles();
    ThreadPool.push_back(std::thread(&Manager::runPipeline, this));
  }

  void dumpStats() {
    std::cerr << "Compiled Regions: " << std::dec << CompiledRegions << "\n";
    std::cerr << "Avg Code Size Reduction: ";
    std::cerr << CompiledRegions ? AvgOptCodeSize / CompiledRegions : 0;
    std::cerr << std::endl;
    std::cerr << "Compiled OI: " << OICompiled << "\n";
    std::cerr << "Compiled LLVM: " << LLVMCompiled << std::endl;
    std::cerr << "LLVM/OI: " << ((float)(LLVMCompiled + 1) / (OICompiled + 1))
              << std::endl;
  }

  ~Manager() {
    // Alert threads to stop
    isRunning = false;

    // Waits the thread finish
    if (ThreadPool.size() != 0) {
      while (!isFinished) {
      }

      for (unsigned i = 0; i < ThreadPool.size(); i++) {
        if (!ThreadPool[i].joinable())
          ThreadPool[i].join();
      }
    }
  }

  void setOptPolicy(OptPolitic OM) { OptMode = OM; }

  void
  setCustomOpts(std::unordered_map<uint32_t, std::vector<std::string>> *COpts) {
    CustomOpts = COpts;
    OptMode = Custom;
  }

  void setLockMode() { LockMode = true; }

  bool getLockMode() { return LockMode; }

  void setROIMode() { ROIMode = true; }

  bool getROIMode() { return ROIMode; }

  void setROI(ROIInfo R) { ROI = R; }

  ROIInfo getROI() { return ROI; }

  unsigned getCompiledRegions(void) { return CompiledRegions; }

  unsigned getOICompiled(void) { return OICompiled; }

  bool getRegionRecording(void) { return static_cast<bool>(isRegionRecorging); }

  bool isRegionEntry(uint32_t EntryAddress) {
    if (NativeRegions[EntryAddress] != 0)
      return true;
    else {
      OIRegionsMtx.lock_shared();
      bool hasRegion = OIRegions.count(EntryAddress) != 0;
      OIRegionsMtx.unlock_shared();
      return hasRegion;
    }
  }

  void setRegionRecorging(bool value) { isRegionRecorging = value; }

  unsigned getLLVMCompiled(void) { return LLVMCompiled; }

  float getAvgOptCodeSize(void) { return AvgOptCodeSize; }

  void setToLoadRegions(std::string path, bool InLLVMFormat = true,
                        bool WholeCompilation = false) {
    IsToLoadRegions = true;
    IsToDoWholeCompilation = WholeCompilation;
    IsToLoadBCFormat = InLLVMFormat;

    RegionPath = path;
    if (RegionPath.back() != '/')
      RegionPath += '/';
  }

  bool addOIRegion(uint32_t, OIInstList);

  int32_t jumpToRegion(uint32_t);

  inline bool isNativeRegionEntry(uint32_t EntryAddress) {
    return (NativeRegions[EntryAddress] != 0);
  }

  size_t getNumOfOIRegions() { return NumOfOIRegions; }

  float getAvgRegionsSize() {
    uint64_t total;
    for (auto Region : OIRegions)
      total += Region.second.size();
    return (float)total / getNumOfOIRegions();
  }

  bool inCodeCache(uint32_t Addrs) {
    int i = 0;
    for (auto Region : OIRegions) {
      for (auto InstAddr : Region.second)
        if (InstAddr[0] == Addrs)
          return true;

      if (i > OIRegions.size())
        break;

      ++i;
    }
    return false;
  }

  OIInstList getCompiledOIRegion(uint32_t EntryAddrs) {
    return CompiledOIRegions[EntryAddrs];
  }

  void loadOIRegionsFromFiles();

  void mergeOIRegions();

  void dumpRegions(bool MergeRegions = false, bool OnlyOI = false) {
    while (getNumOfOIRegions() != 0) {
    }
    if (!OnlyOI) {
      std::cerr << "Dumping IR regions!\n";
      for (auto &M : IRRegions) {
        std::error_code EC;
        llvm::raw_fd_ostream OS("r" + std::to_string(M.first) + ".bc", EC,
                                llvm::sys::fs::F_None);
        WriteBitcodeToFile(*M.second, OS);
        OS.flush();
      }
      if (MergeRegions) {
        std::cerr << "Merging OI regions!\n";
        mergeOIRegions();
      }
    }
    std::cerr << "Dumping OI regions!\n";
    for (auto OIRegion : CompiledOIRegions) {
      std::error_code EC;
      llvm::raw_fd_ostream OS("r" + std::to_string(OIRegion.first) + ".oi", EC,
                              llvm::sys::fs::F_None);
      for (auto OIInsts : OIRegion.second)
        OS << OIInsts[0] << "\t" << OIInsts[1] << "\t"
           << OIPrinter::getString(OIDecoder::decode(OIInsts[1])) << "\n";
      OS.flush();
    }

    std::error_code EC;
    llvm::raw_fd_ostream OS("regions.order", EC, llvm::sys::fs::F_None);
    for (auto A : IRRegionsKey)
      OS << A << "\n";

    OS.flush();
  }

  std::unordered_map<uint32_t, OIInstList>::iterator oiregions_begin() {
    return CompiledOIRegions.begin();
  };
  std::unordered_map<uint32_t, OIInstList>::iterator oiregions_end() {
    return CompiledOIRegions.end();
  }; // FIXME: Not Thread Safe
};
} // namespace dbt

#endif
