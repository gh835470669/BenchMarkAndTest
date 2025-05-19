add_executable(
    VirtualMethod
    virtual_method.cpp
)
target_link_libraries(
    VirtualMethod
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(VirtualMethod)
