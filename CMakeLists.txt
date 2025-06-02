cmake_minimum_required(VERSION 3.10)
SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_C_FLAGS "-O0")

project(Arrays-Lists)

add_library(DataStructures_lib INTERFACE)
target_include_directories(DataStructures_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_executable(menu ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp    
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Menu.cpp
)
target_link_libraries(menu DataStructures_lib)

add_executable(
    test ${CMAKE_CURRENT_SOURCE_DIR}/src/mainTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Benchmark.cpp
)
target_link_libraries(test DataStructures_lib)
