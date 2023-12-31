#include "make_frontend_action.h"
#include "make_ast_consumer.h"
#include "clang/AST/ASTConsumer.h"
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/CompilerInstance.h>

namespace {

class frontend_action : public clang::ASTFrontendAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &compiler,
                    llvm::StringRef in_file) override {
    return cc_index::make_ast_consumer(compiler, in_file);
  }
};

} // namespace

std::unique_ptr<clang::FrontendAction> cc_index::make_frontend_action() {
  return std::make_unique<frontend_action>();
}
