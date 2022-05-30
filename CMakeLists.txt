cmake_minimum_required(VERSION 3.22)
project(BigNumber LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(OPTIONS -Wall -Wextra -Werror -pedantic -Wshadow -Wsign-conversion)

file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# The library
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(${PROJECT_NAME} PRIVATE ${OPTIONS})

# The tests
add_executable(tests ${PROJECT_SOURCE_DIR}/tests/main.cpp)
target_link_libraries(tests ${PROJECT_NAME})
target_compile_options(tests PRIVATE ${OPTIONS})
