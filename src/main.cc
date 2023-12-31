#include "index.h"
#include <iostream>
#include <vector>

namespace {

std::string read_stdin() {
  std::string s;
  // 64k buffer seems sufficient
  std::streamsize buffer_sz = 65536;
  std::vector<char> buffer(buffer_sz);
  s.reserve(buffer_sz);

  auto rdbuf = std::cin.rdbuf();
  while (auto cnt_char = rdbuf->sgetn(buffer.data(), buffer_sz)) {
    s.insert(s.end(), buffer.data(), buffer.data() + cnt_char);
  }

  return s;
}

} // namespace

int main(int argc, const char **argv) {
  return cc_index::index(read_stdin().c_str(), argv + 1, argc - 1);
}
