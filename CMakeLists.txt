cmake_minimum_required(VERSION 3.22)
project(BigInt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# The library
add_library(BigInt STATIC ${SOURCES} ${HEADERS})
target_include_directories(BigInt PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(BigInt PRIVATE -Wall -Wextra -Werror -pedantic -Wshadow -Wsign-conversion)

# The tests
add_executable(tests ${PROJECT_SOURCE_DIR}/tests/main.cpp)
target_link_libraries(tests BigInt)
target_compile_options(tests PRIVATE -Wall -Wextra -Werror -pedantic -Wshadow -Wsign-conversion)
