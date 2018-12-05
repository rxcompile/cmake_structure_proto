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
    PRIVATE
    )
if(ENABLE_UNIT_TESTING)
    add_subdirectory(test)
endif()
