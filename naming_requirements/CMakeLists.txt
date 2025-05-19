add_executable(
    NamingRequirements
    naming_requires_basic.cpp
)
target_link_libraries(
    NamingRequirements
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(NamingRequirements)
