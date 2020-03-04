cmake_minimum_required(VERSION 3.13)

project(sl VERSION 0.1
           DESCRIPTION "A small lisp"
           LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(core)
add_subdirectory(repl)
add_subdirectory(tests)

