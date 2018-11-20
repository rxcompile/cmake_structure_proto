add_library(cstdmf
    singleton.cpp
    include/cstdmf/singleton.hpp
)
add_library(WG::cstdmf ALIAS cstdmf)

set_target_properties(cstdmf PROPERTIES STATIC_LIBRARY_OPTIONS "/ignore:4221")
set_target_properties(cstdmf PROPERTIES LINK_OPTIONS "/ignore:4221")
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
