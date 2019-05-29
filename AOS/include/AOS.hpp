#include <llvm/IR/Module.h>

namespace aos {

class AOS {

public:
    void run(llvm::Module *M);
};

} // namespace aos
