#include "index.h"
#include "make_frontend_action.h"
#include <clang/Tooling/Tooling.h>

int cc_index::index(const char *code, const char **opts, int n) {
  std::vector<std::string> args(opts, opts + n);

  return clang::tooling::runToolOnCodeWithArgs(cc_index::make_frontend_action(),
                                               code, args)
             ? 0
             : -1;
}