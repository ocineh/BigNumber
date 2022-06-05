project(BigNumber LANGUAGES CXX)

file(GLOB SOURCES *.cpp big_float/*.cpp big_int/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)
target_compile_options(${PROJECT_NAME} PRIVATE ${OPTIONS})
