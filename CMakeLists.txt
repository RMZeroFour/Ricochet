cmake_minimum_required(VERSION 3.20)
project(Ricochet CXX)

add_subdirectory(src bin)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()