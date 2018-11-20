add_executable(resmgr_test
    test_api.cpp
)

find_package(GTest REQUIRED)

target_link_libraries(resmgr_test
    PRIVATE
        WG::resmgr
        GTest::GTest
)
add_test(NAME resmgrTest COMMAND resmgr_test)
