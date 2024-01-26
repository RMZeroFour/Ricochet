# ---- Minimum CMake version ----
cmake_minimum_required(VERSION 3.22)

# ---- Project details ----
project(
	Ricochet
	VERSION 0.1
	DESCRIPTION "A game of pinball, made with C++ and SDL."
	HOMEPAGE_URL https://github.com/RMZeroFour/Ricochet
	LANGUAGES CXX
)

# ---- Helper modules ----
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(EnableCCache)
include(BuildOptions)
include(CTest)

add_subdirectory(src bin)