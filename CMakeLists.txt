cmake_minimum_required(VERSION 3.10)
SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_C_FLAGS "-O0")

project(HashTableProject)

if(MSVC)
    add_compile_options(/W0) 
endif()

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(HashTableProject ${SOURCES})