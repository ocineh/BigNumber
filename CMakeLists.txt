cmake_minimum_required(VERSION 3.22)
project(BigInt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
add_compile_options("-Os")

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/big_int*.cpp)
add_library(BigInt STATIC ${SOURCES} ${PROJECT_SOURCE_DIR}/include/big_int.hpp)
target_include_directories(BigInt PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(BigIntMath STATIC ${PROJECT_SOURCE_DIR}/src/big_int_math.cpp ${PROJECT_SOURCE_DIR}/include/big_int_math.hpp)
target_include_directories(BigIntMath PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(tests ${PROJECT_SOURCE_DIR}/tests/main.cpp)
target_link_libraries(tests BigInt BigIntMath)
