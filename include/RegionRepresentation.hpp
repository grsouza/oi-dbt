#pragma once

#include <string>

namespace llvm {
class Module;
};

namespace dbt {

std::string GetRegionRepresentation(const llvm::Module *);
};
