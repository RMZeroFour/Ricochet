include_guard(GLOBAL)

include(CMakeDependentOption)

# ---- Project/Debugging Customization ----
option(
	Ricochet_DEVELOPER_MODE
	"Master enable for debug features"
	${Ricochet_IS_TOP_LEVEL}
)
cmake_dependent_option(
	Ricochet_ENABLE_DEBUG_LOGGING
	"Enables debug level log statements"
	ON #[[if]] "Ricochet_DEVELOPER_MODE" #[[else]] OFF
)
cmake_dependent_option(
	Ricochet_ENABLE_IMGUI
	"Enables drawing debug UI with imgui"
	ON #[[if]] "Ricochet_DEVELOPER_MODE" #[[else]] OFF
)

# ---- Buildsystem Customization ----
option(
	Ricochet_USE_COMPILER_CACHE
	"Enables tools like ccache (see also: CCACHE_PROGRAM_NAMES)"
	ON
)

cmake_dependent_option(
	Ricochet_VENDOR_IMGUI
	"Download imgui sources on configure (see also: FETCHCONTENT_SOURCE_DIR_IMGUI)"
	ON #[[if]] "Ricochet_ENABLE_IMGUI" #[[else]] OFF
)

# other options like _build_testing, _build_shared_libs, _skip_install_rules