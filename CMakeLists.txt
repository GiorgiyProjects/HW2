cmake_minimum_required(VERSION 3.5)

project(allocator)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(allocator main.cpp myAllocator.hpp myContainer.hpp mapHelper.hpp)
add_executable(tests tests.cpp myAllocator.hpp myContainer.hpp mapHelper.hpp)

set_target_properties(allocator tests PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

enable_testing()
add_test(tests tests)