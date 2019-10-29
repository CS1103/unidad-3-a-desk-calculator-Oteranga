cmake_minimum_required(VERSION 3.13.4)
project(DeskCalculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(DeskCalculator main.cpp error.h lexer.cpp lexer.h parser_implement.h table.h catch.hpp)