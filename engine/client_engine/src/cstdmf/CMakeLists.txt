add_library(cstdmf
    singleton.cpp
    include/cstdmf/singleton.hpp
)
add_library(WG::cstdmf ALIAS cstdmf)

target_include_directories(cstdmf PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )
target_compile_features(cstdmf PUBLIC cxx_std_17)
target_link_libraries(cstdmf
    PUBLIC
    PRIVATE
    )
if(ENABLE_UNIT_TESTING)
    add_subdirectory(test)
endif()
