
#include <memory>
#include <llvm/IR/Module.h>

namespace aos {

struct DNA;

class AOSSolver {
public:
    virtual std::unique_ptr<DNA> solve(llvm::Module *M) = 0;
};
} // namespace aos