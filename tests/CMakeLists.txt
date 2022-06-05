project(BigNumberTest LANGUAGES CXX)

add_executable(tests main.cpp)
target_link_libraries(tests BigNumber)
target_compile_options(tests PRIVATE ${OPTIONS})
