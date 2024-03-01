include_guard(GLOBAL)

function(VendorImGui)
	cmake_parse_arguments(PARSE_ARGV 0 arg "" "IF" "")
	if((DEFINED arg_IF AND NOT arg_IF) OR TARGET imgui::imgui)
		return()
	endif()
	
	# To use an existing checkout, whether clean or modified,
	# set FETCHCONTENT_SOURCE_DIR_IMGUI to the correct directory,
	# or leave empty, to fetch sources at configure time.
	set(
		FETCHCONTENT_SOURCE_DIR_IMGUI "" 
		CACHE PATH "Path to local imgui checkout (unset to download on configure)"
	)
	
	# If fetching sources on configure, use FETCHCONTENT_IMGUI_URL
	# and FETCHCONTENT_IMGUI_SHA256 to modify what sources are fetched.
	set(
		FETCHCONTENT_URL_IMGUI 
		"https://github.com/ocornut/imgui/archive/refs/tags/v1.90.1.tar.gz" 
		CACHE STRING "URL of imgui archive to fetch"
	)
	set(
		FETCHCONTENT_SHA256_IMGUI
		"21dcc985bb2ae8fe48047c86135dbc438d6980a8f2e08babbda5be820592f282"
		CACHE STRING "SHA256 hash of imgui archive to fetch"
	)
	
	include(FetchContent)
	FetchContent_Declare(
		imgui
		URL ${FETCHCONTENT_URL_IMGUI}
		URL_HASH SHA256=${FETCHCONTENT_SHA256_IMGUI}
	)
	FetchContent_MakeAvailable(imgui)
		
	add_library(imgui INTERFACE)
	add_library(imgui::imgui ALIAS imgui)
	
	target_sources(
		imgui
		INTERFACE
			${imgui_SOURCE_DIR}/imgui.cpp
			${imgui_SOURCE_DIR}/imgui_demo.cpp
			${imgui_SOURCE_DIR}/imgui_draw.cpp
			${imgui_SOURCE_DIR}/imgui_tables.cpp
			${imgui_SOURCE_DIR}/imgui_widgets.cpp
			${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
			${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
			${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
	)
	
	target_include_directories(
		imgui
		INTERFACE
			${imgui_SOURCE_DIR}
			${imgui_SOURCE_DIR}/backends
			${imgui_SOURCE_DIR}/misc/cpp
	)
	
	find_package(SDL2 REQUIRED)
	target_link_libraries(
		imgui
		INTERFACE
			$<IF:$<TARGET_EXISTS:SDL2::SDL2>,
				SDL2::SDL2,SDL2::SDL2-static>
	)
	
endfunction()