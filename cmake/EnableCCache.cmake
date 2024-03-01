include_guard(GLOBAL)

function(UseCompilerCache)
	cmake_parse_arguments(PARSE_ARGV 0 arg "" "IF" "")
	if(DEFINED arg_IF AND NOT arg_IF)
		return()
	endif()

	# To modify the compiler cache program, add the directory 
	# containing the program to CMAKE_PROGRAM_PATH, and the name
	# of the program to CCACHE_PROGRAM_NAMES.
	set(
		CCACHE_PROGRAM_NAMES 
		"ccache" 
		CACHE STRING "Names of programs to use as compiler cache"
	)
	
	find_program(CCACHE_PROGRAM NAMES ${CCACHE_PROGRAM_NAMES})
	
	if(CCACHE_PROGRAM)
		set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
		set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
		message(STATUS "Found and enabled ccache at: ${CCACHE_PROGRAM}")
	else()
		message(STATUS "Could not find ccache at: ${CCACHE_PROGRAM}")
	endif()
endfunction()