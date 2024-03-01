# ---- Minimum CMake version ----
cmake_minimum_required(VERSION 3.22)

# ---- Project details ----
project(
	Ricochet
	VERSION 0.1.0
	DESCRIPTION "A game of pinball, made with C++ and SDL."
	HOMEPAGE_URL https://github.com/RMZeroFour/Ricochet
	LANGUAGES CXX
)
set(Ricochet_MAINTAINER RMZeroFour)

# ---- Helper modules ----
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(BuildOptions)
include(GetPlatform)
include(EnableCCache)

GetPlatform(
	WINDOWS Ricochet_PLATFORM_WINDOWS
	LINUX Ricochet_PLATFORM_LINUX
	OTHERWISE Ricochet_PLATFORM_UNKNOWN
)

UseCompilerCache(IF ${Ricochet_USE_COMPILER_CACHE})

# ---- Executable subdirectory ----
add_subdirectory(src bin)