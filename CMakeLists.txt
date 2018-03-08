cmake_minimum_required(VERSION 3.9)
project(load_balancing_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(load_balancing_test main.cpp task_thread.cpp task_thread.hpp thread_pool.cpp thread_pool.hpp)