#pragma once

#include <memory>

namespace clang {
class FrontendAction;
} // namespace clang

namespace cc_index {

std::unique_ptr<clang::FrontendAction> make_frontend_action();

} // namespace cc_index