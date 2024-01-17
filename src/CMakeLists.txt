find_package(SDL2 REQUIRED CONFIG)

# Core library containing sources common to 
# both the executable and unit tests
add_library(Ricochet_core INTERFACE)
target_sources(
    Ricochet_core
    INTERFACE
        statemachine.cpp
)
target_include_directories(
    Ricochet_core 
    INTERFACE 
        .
)

# Main executable for the game
add_executable(Ricochet_exe)
set_target_properties(
    Ricochet_exe 
    PROPERTIES 
        OUTPUT_NAME Ricochet
)
target_sources(
    Ricochet_exe
    PRIVATE 
        main.cpp
)
target_link_libraries(
    Ricochet_exe 
    PRIVATE 
        Ricochet_core 
        SDL2::SDL2
        SDL2::SDL2main
)
