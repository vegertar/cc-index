#pragma once

#include <memory>
#include <string_view>

namespace clang {
class ASTConsumer;
class CompilerInstance;
} // namespace clang

namespace cc_index {

std::unique_ptr<clang::ASTConsumer>
make_ast_consumer(clang::CompilerInstance &compiler, std::string_view in_file);

}