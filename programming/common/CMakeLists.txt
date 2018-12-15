cmake_minimum_required(VERSION 3.13)
project(encore_common VERSION 1.0.0)

# All posible options for building this project
option(BUILD_SHARED_LIBS "Compile targets as shared libraries" OFF)
option(ENABLE_UNIT_TESTING "Add testing projects for all supported targets" OFF)

# Define all subdirectories
SET(_sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)
FILE(GLOB _children RELATIVE ${_sources_dir} ${_sources_dir}/*)
SET(_directories "")
FOREACH(_child ${_children})
    IF(IS_DIRECTORY ${_sources_dir}/${_child})
        LIST(APPEND _directories ${_child})
        message(STATUS "Adding target sources: ${_child}")
    ENDIF()
ENDFOREACH()

######### CMake setup ##########
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# usefull scripts
include(cotire)
include(conan)
include(CMakePackageConfigHelpers)

# package management
conan_check()
conan_cmake_run(
    CONANFILE conanfile.py
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing
)

# default postfixes
set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_MINSIZEREL_POSTFIX _mz)
set(CMAKE_RELWITHDEBINFO_POSTFIX _rd)

# setup libraries
set(_libraries_public_includes)
set(_libraries_targets)
foreach(_lib ${_directories})
    set(_path src/${_lib})
    # add sources
    add_subdirectory(${_path})
    # cache for install step
    get_directory_property(_dir_targets DIRECTORY ${_path} BUILDSYSTEM_TARGETS)
    foreach(_dir_target ${_dir_targets})
        get_target_property(_type ${_dir_target} TYPE)
        get_target_property(_excl ${_dir_target} EXCLUDE_FROM_ALL)
        if(_type STREQUAL UTILITY OR _excl)
            continue()
        endif()
        get_target_property(_target_public_includes ${_dir_target} INTERFACE_INCLUDE_DIRECTORIES)
        if(_target_public_includes)
            list(APPEND _public_includes ${_target_public_includes})
        endif()
        list(APPEND _libraries_targets ${_dir_target})
    endforeach()
endforeach()

# install targets
install(
    TARGETS ${_libraries_targets}
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
install(
    DIRECTORY ${_public_includes}
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# install cmake scripts
write_basic_package_version_file(encore_commonConfigVersion.cmake
    COMPATIBILITY SameMajorVersion
)
install(FILES
    cmake/encore_commonConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/encore_commonConfigVersion.cmake
    DESTINATION cmake
)