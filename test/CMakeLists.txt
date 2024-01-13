find_package(GTest REQUIRED CONFIG)

add_executable(Ricochet_test gtest_test.cpp)
target_link_libraries(Ricochet_test PRIVATE Ricochet_core GTest::gtest GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(Ricochet_test)