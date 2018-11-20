cmake_minimum_required(VERSION 3.10)
project(stub_client VERSION 1.0.0)

# for now engine is out_of_tree build
# later it can be just like other conan package
add_subdirectory(../engine/client_engine engine_build)

add_executable(stub_client
    src/main.cpp
    )
target_link_libraries(stub_client PRIVATE
    WG::encore_engine
    )
