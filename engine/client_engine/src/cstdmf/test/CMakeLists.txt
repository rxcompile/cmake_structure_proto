add_executable(cstdmf_test
    test_api.cpp
)

find_package(GTest REQUIRED)

target_link_libraries(cstdmf_test
    PRIVATE
        WG::cstdmf
        GTest::GTest
)
add_test(NAME cstdmfTest COMMAND cstdmf_test)
