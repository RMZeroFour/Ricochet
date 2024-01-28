# ---- Third party libraries ----
find_package(argh REQUIRED CONFIG)
find_package(SDL2 REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)

if (Ricochet_BUILD_TESTS)
	find_package(GTest REQUIRED CONFIG)
endif()

# ---- Auto-generated files ----
set(generated_include_dir ${CMAKE_CURRENT_BINARY_DIR}/include)
configure_file(
	generated/buildinfo.h.in
	${generated_include_dir}/generated/buildinfo.h
	@ONLY
)

# ---- Main application ----
add_executable(Ricochet_exe)

set_target_properties(
	Ricochet_exe
	PROPERTIES
		OUTPUT_NAME Ricochet
)

target_compile_features(
	Ricochet_exe
	PRIVATE
		cxx_std_17
)

target_sources(
	Ricochet_exe
	PRIVATE
		main.cpp
		statemachine/statemachine.cpp
		game/states/argsparserstate.cpp
		game/states/loginitstate.cpp
		game/states/sdlinitstate.cpp
		game/states/dummystate.cpp
		game/states/sdlquitstate.cpp
)

target_include_directories(
	Ricochet_exe
	PRIVATE
		.
		${generated_include_dir}
)

target_link_libraries(
	Ricochet_exe
	PRIVATE
		argh
		SDL2::SDL2
		SDL2::SDL2main
		spdlog::spdlog
)

install(TARGETS Ricochet_exe RUNTIME)

# ---- Tests target ----
if (Ricochet_BUILD_TESTS)
	add_executable(Ricochet_test)

	target_compile_features(
		Ricochet_test
		PRIVATE
			cxx_std_17
	)

	target_sources(
		Ricochet_test
		PRIVATE
			statemachine/statemachine.cpp
			statemachine/statemachine.test.cpp
	)

	target_include_directories(
		Ricochet_test
		PRIVATE
			.
			${generated_include_dir}
	)

	target_link_libraries(
		Ricochet_test
		PRIVATE
			GTest::gtest
			GTest::gmock_main
	)

	include(GoogleTest)
	gtest_discover_tests(Ricochet_test)
endif()
