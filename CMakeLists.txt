cmake_minimum_required(VERSION "3.20.0")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(DSA)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")
message(STATUS "Sources found: ${MY_SOURCES}")

add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

# Collect all subdirectories containing headers
file(GLOB_RECURSE ALL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h")

set(INCLUDE_DIRS "")

foreach(HEADER ${ALL_HEADERS})
    get_filename_component(DIR ${HEADER} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${DIR})
endforeach()

list(REMOVE_DUPLICATES INCLUDE_DIRS)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})