cmake_minimum_required(VERSION 3.10)
SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_C_FLAGS "-O0")

project(HashTableProject)

# Znajdź wszystkie pliki źródłowe
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

# Utwórz bibliotekę z funkcjami podstawowymi
add_library(DataStructures_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(DataStructures_lib PUBLIC include/)

# Plik wykonywalny z testami
add_executable(tests src/main.cpp)
target_link_libraries(tests DataStructures_lib)

# Plik wykonywalny z menu (tylko jeśli plik istnieje)
add_executable(menu src/menu.cpp)
target_link_libraries(menu DataStructures_lib)