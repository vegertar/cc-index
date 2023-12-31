cmake_minimum_required(VERSION 3.20)
project(cc-index VERSION 1.0.0)
configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Werror
  -Wno-unused-parameter
  -fno-exceptions
  -fno-rtti
)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

find_package(Clang REQUIRED)

add_library(cc-index
  lib/index.cc
  lib/make_frontend_action.cc
  lib/make_ast_consumer.cc
)

target_link_libraries(cc-index PRIVATE
  clang-cpp
  LLVM
)
target_include_directories(cc-index PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/include"
)

add_executable(main
  src/main.cc
)

target_link_libraries(main cc-index)
set_property(TARGET main PROPERTY OUTPUT_NAME cc-index)
