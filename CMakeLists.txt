cmake_minimum_required(VERSION 3.5)

project(allocator)

add_executable(allocator main.cpp myAllocator.hpp myContainer.hpp)
set_target_properties(allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

