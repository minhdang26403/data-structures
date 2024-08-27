cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For clangd
set(CMAKE_CXX_STANDARD 20) # Compile as C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Require C++20 support

project(LearnCppConcurrency VERSION 2024.1
  DESCRIPTION "Implementing data structures and standard library features"
  LANGUAGES C CXX)

# #####################################################################################################################
# COMPILER SETUP
# #####################################################################################################################

# Set the binary directory within the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT DEFINED SANITIZER)
  set(SANITIZER thread)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -fsanitize=${SANITIZER} -fno-omit-frame-pointer -fno-optimize-sibling-calls")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

include_directories(include)
add_subdirectory(test)