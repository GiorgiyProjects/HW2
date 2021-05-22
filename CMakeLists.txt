cmake_minimum_required(VERSION 3.5)

project(06.allocator)

add_executable(my_allocator my_allocator.cpp main.cpp my_allocator.h myContainer.cpp myContainer.h)
set_target_properties(my_allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

