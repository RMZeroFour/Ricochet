find_package(SDL2 REQUIRED CONFIG)

add_library(Ricochet_core INTERFACE)
target_include_directories(Ricochet_core INTERFACE .)

add_executable(Ricochet_exe main.cpp)
set_target_properties(Ricochet_exe PROPERTIES TARGET_NAME Ricochet)
target_link_libraries(Ricochet_exe PRIVATE Ricochet_core SDL2::SDL2 SDL2::SDL2main)