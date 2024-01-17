find_package(GTest REQUIRED CONFIG)

# Executable for unit tests
add_executable(Ricochet_test)
target_sources(
    Ricochet_test
    PRIVATE 
        gtest_test.cpp
        statemachine_test.cpp
)
target_link_libraries(
    Ricochet_test
    PRIVATE
        Ricochet_core
        GTest::gtest
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(Ricochet_test)