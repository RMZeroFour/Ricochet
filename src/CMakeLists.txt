# ---- Third party libraries ----
find_package(argh REQUIRED CONFIG)
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)

if (Ricochet_ENABLE_IMGUI)
	find_package(imgui REQUIRED CONFIG)
endif()

# ---- Auto-generated files ----
set(_generated_include_dir ${CMAKE_CURRENT_BINARY_DIR}/include)
configure_file(buildinfo.h.in ${_generated_include_dir}/buildinfo.h @ONLY)

# ---- Main application ----
add_executable(Ricochet)

target_compile_features(Ricochet PRIVATE cxx_std_17)

target_sources(
	Ricochet
	PRIVATE
		main.cpp
		statemachine/statemachine.cpp
		game/states/argsparserstate.cpp
		game/states/loginitstate.cpp
		game/states/sdlinitstate.cpp
		game/states/imguiinitstate.cpp
		game/states/dummystate.cpp
		game/states/imguiquitstate.cpp
		game/states/sdlquitstate.cpp
		game/states/crashstate.cpp
)

target_include_directories(
	Ricochet
	PRIVATE
		.
		${_generated_include_dir}
)

target_link_libraries(
	Ricochet
	PRIVATE
		argh
		$<IF:$<TARGET_EXISTS:SDL2::SDL2>,
			SDL2::SDL2,SDL2::SDL2-static>
		$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
		$<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,
			SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
		spdlog::spdlog
)

if (Ricochet_ENABLE_IMGUI)
	target_link_libraries(Ricochet PRIVATE imgui::imgui)
endif()

# During build time, copy the assets directory to near the build directory.
add_custom_command(
	TARGET Ricochet POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/data/
		${Ricochet_STATIC_DATA_DIR}
	WORKING_DIRECTORY $<TARGET_FILE_DIR:Ricochet>
	VERBATIM
)
	

# ---- Install rules ----
include(GNUInstallDirs)
install(
	TARGETS Ricochet
	RUNTIME 
		DESTINATION ${CMAKE_INSTALL_BINDIR}
		COMPONENT Ricochet-Runtime
)
install(
	DIRECTORY ${CMAKE_SOURCE_DIR}/data/
	DESTINATION ${CMAKE_INSTALL_BINDIR}/${Ricochet_STATIC_DATA_DIR}
	COMPONENT Ricochet-Assets
)

# ---- Package info ----
set(CPACK_PACKAGE_NAME "Ricochet")
set(CPACK_PACKAGE_VENDOR "RMZeroFour")
include(CPack)