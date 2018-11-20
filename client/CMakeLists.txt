cmake_minimum_required(VERSION 3.10)
project(stub_client VERSION 1.0.0)

add_subdirectory(../engine/client_engine)

add_executable(stub_client main.cpp)
target_link_libraries(stub_client PRIVATE
    WG::encore_engine
    )
