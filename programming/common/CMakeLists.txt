cmake_minimum_required(VERSION 3.12)
project(encore_common VERSION 1.0.0)

option(BUILD_SHARED_LIBS OFF)
option(ENABLE_UNIT_TESTING OFF)

# package management
include(cmake/conan.cmake)
conan_check()
conan_cmake_run(
    CONANFILE conanfile.py
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing
)

# common libs
# TODO: seems like BW_LIBRARIES...
set(_libraries
    networking
    cstdmf
    # TODO: add more
)

# default postfixes
set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_MINSIZEREL_POSTFIX _mz)
set(CMAKE_RELWITHDEBINFO_POSTFIX _rd)

# add libraries sources
foreach(_lib ${_libraries})
    add_subdirectory(src/${_lib})
endforeach()

# install targets
install(
    TARGETS ${_libraries}
    EXPORT encore_commonTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(
    EXPORT encore_commonTargets
    DESTINATION cmake
    FILE encore_commonTargets.cmake
    NAMESPACE WG::
)

# install public include headers
set(_libraries_public_includes)
foreach(_lib ${_libraries})
    list(APPEND _libraries_public_includes "src/${_lib}/include/${_lib}")
endforeach()
install(
    DIRECTORY ${_libraries_public_includes}
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

# install cmake scripts
include(CMakePackageConfigHelpers)
write_basic_package_version_file(encore_commonConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)
install(FILES 
    cmake/encore_commonConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/encore_commonConfigVersion.cmake
    DESTINATION cmake)

mark_as_advanced(_libraries _libraries_public_includes)