cmake_minimum_required(VERSION 3.22)
project(nary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(nary
    src/main.cpp
    src/lexer.cpp
)

target_include_directories(nary PRIVATE include)
