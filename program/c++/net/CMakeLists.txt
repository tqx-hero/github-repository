cmake_minimum_required(VERSION 4.2)
project(net)

set(CMAKE_CXX_STANDARD 14)

add_executable(net main.cpp
        byte_order/byteOrder.cpp)
