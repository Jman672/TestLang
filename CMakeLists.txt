cmake_minimum_required(VERSION 3.20)

project(TestLang)

set(CMAKE_CXX_STANDARD 20)

add_executable(test src/main.cpp
        src/includeFile.h
        src/tokenization.hpp
        src/parser.hpp
        src/generate.hpp)