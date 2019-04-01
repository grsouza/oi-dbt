
#include "AOSRegionCharacterizationStrategy.hpp"

using namespace dbt;

std::string
DNARegionCharacterizationStrategy::getCharacterization(const llvm::Module &M) {
  std::string Repr;

  for (auto &Func : M) {
    for (auto &BB : Func) {
      for (auto &Inst : BB) {
        switch (Inst.getOpcode()) {
        case llvm::Instruction::Br:
          Repr.push_back('A');
          break;

        case llvm::Instruction::Switch:
          Repr.push_back('B');
          break;

        case llvm::Instruction::IndirectBr:
          Repr.push_back('C');
          break;

        case llvm::Instruction::Ret:
        case llvm::Instruction::Invoke:
        case llvm::Instruction::Resume:
        case llvm::Instruction::Unreachable:
          Repr.push_back('D');
          break;

        case llvm::Instruction::Add:
        case llvm::Instruction::Sub:
        case llvm::Instruction::Mul:
        case llvm::Instruction::UDiv:
        case llvm::Instruction::SDiv:
        case llvm::Instruction::URem:
        case llvm::Instruction::SRem:
          Repr.push_back('E');
          break;

        case llvm::Instruction::FAdd:
        case llvm::Instruction::FSub:
        case llvm::Instruction::FMul:
        case llvm::Instruction::FDiv:
        case llvm::Instruction::FRem:
          Repr.push_back('F');
          break;

        case llvm::Instruction::Shl:
        case llvm::Instruction::LShr:
        case llvm::Instruction::AShr:
        case llvm::Instruction::And:
        case llvm::Instruction::Or:
        case llvm::Instruction::Xor:
          Repr.push_back('G');
          break;

        case llvm::Instruction::ExtractElement:
        case llvm::Instruction::InsertElement:
        case llvm::Instruction::ShuffleVector:
          Repr.push_back('H');
          break;

        case llvm::Instruction::ExtractValue:
        case llvm::Instruction::InsertValue:
          Repr.push_back('I');
          break;

        case llvm::Instruction::Load:
          Repr.push_back('J');
          break;

        case llvm::Instruction::Store:
          Repr.push_back('K');
          break;

        case llvm::Instruction::Alloca:
          Repr.push_back('L');
          break;

        case llvm::Instruction::Fence:
        case llvm::Instruction::AtomicCmpXchg:
        case llvm::Instruction::AtomicRMW:
          Repr.push_back('M');
          break;

        case llvm::Instruction::GetElementPtr:
          Repr.push_back('N');
          break;

        case llvm::Instruction::Trunc:
        case llvm::Instruction::ZExt:
        case llvm::Instruction::SExt:
        case llvm::Instruction::UIToFP:
        case llvm::Instruction::SIToFP:
        case llvm::Instruction::PtrToInt:
        case llvm::Instruction::IntToPtr:
        case llvm::Instruction::BitCast:
        case llvm::Instruction::AddrSpaceCast:
          Repr.push_back('O');
          break;

        case llvm::Instruction::FPTrunc:
        case llvm::Instruction::FPExt:
        case llvm::Instruction::FPToUI:
        case llvm::Instruction::FPToSI:
          Repr.push_back('P');
          break;

        case llvm::Instruction::ICmp:
        case llvm::Instruction::FCmp:
        case llvm::Instruction::Select:
        case llvm::Instruction::VAArg:
        case llvm::Instruction::LandingPad:
          Repr.push_back('Q');
          break;

        case llvm::Instruction::PHI:
          Repr.push_back('R');
          break;

        case llvm::Instruction::Call:
          Repr.push_back('S');
          break;

        default:
          Repr.push_back('X');
          break;
        }
      }
    }
  }

  return Repr;
}