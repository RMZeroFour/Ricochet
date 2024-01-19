cmake_minimum_required(VERSION 3.20)
project(
    Ricochet
    VERSION 0.1
    DESCRIPTION "A game of pinball, made with C++ and SDL."
    HOMEPAGE_URL https://github.com/RMZeroFour/Ricochet
    LANGUAGES CXX
)

add_subdirectory(src bin)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()