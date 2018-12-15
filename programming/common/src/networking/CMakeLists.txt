option(ENABLE_NETWORKING_UT OFF)

add_library(networking
    protocol.cpp
    include/networking/protocol.hpp
)
add_library(WG::networking ALIAS networking)

target_include_directories(networking PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )
target_compile_features(networking PUBLIC cxx_std_17)
target_link_libraries(networking
    PUBLIC
        WG::cstdmf
    PRIVATE
    )
if(ENABLE_UNIT_TESTING OR ENABLE_NETWORKING_UT)
    add_subdirectory(test)
endif()

# cotiring target
cotire(WG::networking)