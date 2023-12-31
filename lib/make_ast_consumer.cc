#include "make_ast_consumer.h"
#include <clang/AST/DeclGroup.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

namespace {

using namespace clang;
using namespace clang::ast_matchers;

StatementMatcher matcher = forStmt(hasCondition(anything()));

class loop_printer : public MatchFinder::MatchCallback {
public:
  void run(const MatchFinder::MatchResult &result) override {
    llvm::outs() << "for loop.\n";
  }
};

class ast_consumer final : public clang::ASTConsumer {
public:
  ast_consumer() {
    finder.addMatcher(matcher, &printer);
    impl = finder.newASTConsumer();
  }

protected:
  void Initialize(clang::ASTContext &context) override {
    return impl->Initialize(context);
  }

  bool HandleTopLevelDecl(clang::DeclGroupRef dg) override {
    return impl->HandleTopLevelDecl(dg);
  }

  void HandleInterestingDecl(clang::DeclGroupRef dg) override {
    return impl->HandleInterestingDecl(dg);
  }

  void HandleTopLevelDeclInObjCContainer(clang::DeclGroupRef dg) override {
    return impl->HandleTopLevelDeclInObjCContainer(dg);
  }

  void HandleTranslationUnit(clang::ASTContext &ctx) override {
    return impl->HandleTranslationUnit(ctx);
  }

  bool shouldSkipFunctionBody(clang::Decl *d) override {
    return impl->shouldSkipFunctionBody(d);
  }

private:
  loop_printer printer;
  clang::ast_matchers::MatchFinder finder;
  std::unique_ptr<clang::ASTConsumer> impl;
};

} // namespace

std::unique_ptr<clang::ASTConsumer>
cc_index::make_ast_consumer(clang::CompilerInstance &compiler,
                            std::string_view in_file) {
  return std::make_unique<ast_consumer>();
}