find_package(SDL2 REQUIRED CONFIG)

add_executable(Ricochet main.cpp)
target_include_directories(Ricochet PRIVATE .)
target_link_libraries(Ricochet PRIVATE SDL2::SDL2 SDL2::SDL2main)