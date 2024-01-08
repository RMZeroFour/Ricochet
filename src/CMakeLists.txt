find_package(SDL2 REQUIRED CONFIG)

add_executable(Ricochet main.cpp)
target_link_libraries(Ricochet SDL2::SDL2 SDL2::SDL2main)