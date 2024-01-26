include_guard(GLOBAL)

include(CMakeDependentOption)

option(
	Ricochet_DEVELOPER_MODE
	"Master enable for developer options"
	${PROJECT_IS_TOP_LEVEL}
)

cmake_dependent_option(
	Ricochet_BUILD_TESTS
	"Build the tests"
	ON #[[if]] "Ricochet_DEVELOPER_MODE" #[[else]] OFF
)
cmake_dependent_option(
	Ricochet_ENABLE_DEBUG_LOGGING
	"Enables debug level log statements"
	ON #[[if]] "Ricochet_DEVELOPER_MODE" #[[else]] OFF
)