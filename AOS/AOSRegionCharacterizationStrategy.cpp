#include "AOSRegionCharacterizationStrategy.hpp"

using namespace dbt;

std::string DNARegionCharacterizationStrategy::encode(const llvm::Module &M) {
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
          Repr.push_back('D');
          break;

        case llvm::Instruction::Invoke:
          Repr.push_back('E');
          break;

        case llvm::Instruction::Resume:
          Repr.push_back('F');
          break;

        case llvm::Instruction::Unreachable:
          Repr.push_back('G');
          break;

        case llvm::Instruction::Add:
          Repr.push_back('H');
          break;

        case llvm::Instruction::Sub:
          Repr.push_back('I');
          break;

        case llvm::Instruction::Mul:
          Repr.push_back('J');
          break;

        case llvm::Instruction::UDiv:
          Repr.push_back('K');
          break;

        case llvm::Instruction::SDiv:
          Repr.push_back('L');
          break;

        case llvm::Instruction::URem:
          Repr.push_back('M');
          break;

        case llvm::Instruction::SRem:
          Repr.push_back('N');
          break;

        case llvm::Instruction::FAdd:
          Repr.push_back('O');
          break;

        case llvm::Instruction::FSub:
          Repr.push_back('P');
          break;

        case llvm::Instruction::FMul:
          Repr.push_back('Q');
          break;

        case llvm::Instruction::FDiv:
          Repr.push_back('R');
          break;

        case llvm::Instruction::FRem:
          Repr.push_back('S');
          break;

        case llvm::Instruction::Shl:
          Repr.push_back('T');
          break;

        case llvm::Instruction::LShr:
          Repr.push_back('U');
          break;

        case llvm::Instruction::AShr:
          Repr.push_back('V');
          break;

        case llvm::Instruction::And:
          Repr.push_back('X');
          break;

        case llvm::Instruction::Or:
          Repr.push_back('W');
          break;

        case llvm::Instruction::Xor:
          Repr.push_back('Y');
          break;

        case llvm::Instruction::ExtractElement:
          Repr.push_back('Z');
          break;

        case llvm::Instruction::InsertElement:
          Repr.push_back('a');
          break;

        case llvm::Instruction::ShuffleVector:
          Repr.push_back('b');
          break;

        case llvm::Instruction::ExtractValue:
          Repr.push_back('c');
          break;

        case llvm::Instruction::InsertValue:
          Repr.push_back('d');
          break;

        case llvm::Instruction::Load:
          Repr.push_back('e');
          break;

        case llvm::Instruction::Store:
          Repr.push_back('f');
          break;

        case llvm::Instruction::Alloca:
          Repr.push_back('g');
          break;

        case llvm::Instruction::Fence:
          Repr.push_back('h');
          break;

        case llvm::Instruction::AtomicRMW:
          Repr.push_back('i');
          break;

        case llvm::Instruction::AtomicCmpXchg:
          Repr.push_back('j');
          break;

        case llvm::Instruction::GetElementPtr:
          Repr.push_back('k');
          break;

        case llvm::Instruction::Trunc:
          Repr.push_back('l');
          break;

        case llvm::Instruction::ZExt:
          Repr.push_back('m');
          break;

        case llvm::Instruction::SExt:
          Repr.push_back('n');
          break;

        case llvm::Instruction::UIToFP:
          Repr.push_back('o');
          break;

        case llvm::Instruction::SIToFP:
          Repr.push_back('p');
          break;

        case llvm::Instruction::PtrToInt:
          Repr.push_back('q');
          break;

        case llvm::Instruction::IntToPtr:
          Repr.push_back('r');
          break;

        case llvm::Instruction::BitCast:
          Repr.push_back('s');
          break;

        case llvm::Instruction::AddrSpaceCast:
          Repr.push_back('t');
          break;

        case llvm::Instruction::FPTrunc:
          Repr.push_back('u');
          break;

        case llvm::Instruction::FPExt:
          Repr.push_back('v');
          break;

        case llvm::Instruction::FPToUI:
          Repr.push_back('x');
          break;

        case llvm::Instruction::FPToSI:
          Repr.push_back('w');
          break;

        case llvm::Instruction::ICmp:
          Repr.push_back('y');
          break;

        case llvm::Instruction::FCmp:
          Repr.push_back('z');
          break;

        case llvm::Instruction::Select:
          Repr.push_back('0');
          break;

        case llvm::Instruction::VAArg:
          Repr.push_back('1');
          break;

        case llvm::Instruction::LandingPad:
          Repr.push_back('2');
          break;

        case llvm::Instruction::PHI:
          Repr.push_back('3');
          break;

        case llvm::Instruction::Call:
          Repr.push_back('4');
          break;

        default:
          Repr.push_back('5');
          break;
        }
      }
    }
  }

  return Repr;
}