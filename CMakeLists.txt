cmake_minimum_required(VERSION 3.22)

project(MockLib VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mocktesters)
add_library(mocklib INTERFACE)

target_sources(
    mocktesters
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
)

target_include_directories(
    mocklib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    mocktesters
    PRIVATE
        mocklib
)
