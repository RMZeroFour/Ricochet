# ---- Helper modules ----
include(GNUInstallDirs)
include(VendorImGui)

# ---- Third party libraries ----
find_package(argh REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(spdlog REQUIRED)

if(Ricochet_ENABLE_IMGUI)
	VendorImGui(IF ${Ricochet_VENDOR_IMGUI})
	if(NOT TARGET imgui::imgui)
		find_package(imgui REQUIRED)
	endif()
endif()

# ---- Auto-generated files ----
set(generated_include_dir ${CMAKE_CURRENT_BINARY_DIR}/include)
configure_file(buildinfo.h.in ${generated_include_dir}/buildinfo.h @ONLY)

# ---- Main application ----
add_executable(Ricochet_exe)

target_compile_features(Ricochet_exe PRIVATE cxx_std_17)

target_sources(
	Ricochet_exe
	PRIVATE
		main.cpp
		statemachine.cpp
		states/argsparserstate.cpp
		states/loginitstate.cpp
		states/sdlinitstate.cpp
		states/imguiinitstate.cpp
		states/dummystate.cpp
		states/imguiquitstate.cpp
		states/sdlquitstate.cpp
		states/crashstate.cpp
)

target_include_directories(Ricochet_exe PRIVATE . ${generated_include_dir})

target_link_libraries(
	Ricochet_exe
	PRIVATE
		argh
		$<IF:$<TARGET_EXISTS:SDL2::SDL2>,
			SDL2::SDL2,SDL2::SDL2-static>
		$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
		$<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,
			SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
		spdlog::spdlog
		$<TARGET_NAME_IF_EXISTS:imgui::imgui>
)

# ---- Platform specific properties ----
if(Ricochet_PLATFORM_LINUX)
	set_target_properties(
		Ricochet_exe
		PROPERTIES
			OUTPUT_NAME ricochet
	)
elseif (Ricochet_PLATFORM_WINDOWS)
	set_target_properties(
		Ricochet_exe
		PROPERTIES
			OUTPUT_NAME Ricochet
			WIN32_EXECUTABLE ON
	)
endif()

# ---- Build tree layout ----
# During build time, copy the assets directory to near the build directory.
if(Ricochet_PLATFORM_LINUX)
	add_custom_target(
		Ricochet_assets
		${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:Ricochet_exe>/../share/ricochet
		VERBATIM
	)
else()
	add_custom_target(
		Ricochet_assets
		${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:Ricochet_exe>/assets
		VERBATIM
	)
endif()
add_dependencies(Ricochet_exe Ricochet_assets)

# ---- Install rules ----
install(TARGETS Ricochet_exe)

if(Ricochet_PLATFORM_LINUX)
	install(
		DIRECTORY ${CMAKE_SOURCE_DIR}/assets/textures
		DESTINATION ${CMAKE_INSTALL_DATADIR}/ricochet
	)
	
	install(
		FILES ${CMAKE_SOURCE_DIR}/assets/packaging/ricochet.desktop
		DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
	)
	
	install(
		FILES ${CMAKE_SOURCE_DIR}/assets/packaging/ricochet.png
		DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/256x256/apps
	)
else()
	install(
		DIRECTORY ${CMAKE_SOURCE_DIR}/assets/textures
		DESTINATION ${CMAKE_INSTALL_BINDIR}/assets
	)
endif()