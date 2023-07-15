cmake_minimum_required(VERSION 3.10)

project(util-ai VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(
    ${PROJECT_NAME} INTERFACE
)

target_include_directories(
    ${PROJECT_NAME} INTERFACE include
)