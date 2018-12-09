add_executable(networking_test
    test_api.cpp
)

find_package(GTest REQUIRED)

target_link_libraries(networking_test
    PRIVATE
        WG::networking
        GTest::GTest
)
add_test(NAME networkingTest COMMAND networking_test)
