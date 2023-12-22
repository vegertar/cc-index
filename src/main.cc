#include <clang/Tooling/Execution.h>
#include <llvm/Support/CommandLine.h>

int main(int argc, const char **argv) {
  auto exec = clang::tooling::createExecutorFromCommandLineArgs(
      argc, argv, llvm::cl::getGeneralCategory(), nullptr);

  if (!exec) {
    llvm::errs() << llvm::toString(exec.takeError()) << "\n";
    return 1;
  }
}