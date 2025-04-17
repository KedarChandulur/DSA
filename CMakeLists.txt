cmake_minimum_required(VERSION 4.0.1)
project(DSA)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(dsa_exec 
    Source/main.cpp 
    Source/Algorithms/Catalan_Algorithm/CatalanTopDown.cpp
    Source/Algorithms/Catalan_Algorithm/CatalanMemoized.cpp
)

target_include_directories(dsa_exec PUBLIC ${CMAKE_SOURCE_DIR}/Source/Algorithms/Catalan_Algorithm)