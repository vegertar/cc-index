cmake_minimum_required(VERSION 3.20)
project(cc-index VERSION 1.0.0)
configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

file(GLOB LIB_FILES ${PROJECT_SOURCE_DIR}/lib/*.cc)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cc)

find_package(Clang REQUIRED)

add_library(cc-index ${LIB_FILES})
target_link_libraries(cc-index PRIVATE
  clang-cpp
  LLVM
)
target_include_directories(cc-index PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/include"
)

add_executable(main ${SRC_FILES})
target_link_libraries(main cc-index)
set_property(TARGET main PROPERTY OUTPUT_NAME cc-index)
