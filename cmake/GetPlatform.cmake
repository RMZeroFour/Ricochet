include_guard(GLOBAL)

function(GetPlatform)
	set(single_valued WINDOWS LINUX OTHERWISE)
	cmake_parse_arguments(PARSE_ARGV 0 arg "" "${single_valued}" "")

	if(arg_WINDOWS AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
		set(${arg_WINDOWS} TRUE PARENT_SCOPE)
	elseif(arg_LINUX AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
		set(${arg_LINUX} TRUE PARENT_SCOPE)
	elseif(arg_OTHERWISE)
		set(${arg_OTHERWISE} TRUE PARENT_SCOPE)
	endif()
endfunction()
