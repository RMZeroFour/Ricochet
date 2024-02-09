include_guard(GLOBAL)

function(SymlinkAssets _arg_TARGET)
	# Parse function arguments
	cmake_parse_arguments(PARSE_ARGV 1 _arg "" "" "FROM;TO")

	# Check required arguments
	if(NOT _arg_TARGET)
		message(FATAL_ERROR "SymlinkAssets: Target is required.")
	endif()
	if(NOT _arg_FROM)
		message(FATAL_ERROR "SymlinkAssets: Source location of assets required.")
	endif()
	if(NOT _arg_TO)
		message(FATAL_ERROR "SymlinkAssets: Relative destination of assets required.")
	endif()
	
	# Make the symlink
	cmake_path(GET _arg_TO PARENT_PATH _symlink_parent)
	add_custom_command(
		TARGET ${_arg_TARGET} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E make_directory
			${_symlink_parent}
		COMMAND ${CMAKE_COMMAND} -E create_symlink
			${_arg_FROM} #[[at]] ${_arg_TO}
		WORKING_DIRECTORY $<TARGET_FILE_DIR:${_arg_TARGET}>
		VERBATIM
	)
endfunction()