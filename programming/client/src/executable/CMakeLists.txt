add_executable(stub_client
    main.cpp
)

target_link_libraries(stub_client
    PUBLIC
    PRIVATE
        WG::cstdmf
)
