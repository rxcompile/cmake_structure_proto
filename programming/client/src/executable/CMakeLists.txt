add_executable(stub_client
    main.cpp
)

find_package(encore_common REQUIRED)

target_link_libraries(stub_client
    PUBLIC
    PRIVATE
        WG::cstdmf
)

cotire(stub_client)