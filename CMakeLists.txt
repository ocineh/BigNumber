cmake_minimum_required(VERSION 3.22)
project(BigNumber LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(OPTIONS -Wall -Wextra -Werror -pedantic -Wshadow -Wsign-conversion)

# The library
add_subdirectory(src)

# The tests
enable_testing()
include(CTest)
add_subdirectory(tests)
