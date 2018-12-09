cmake_minimum_required(VERSION 3.12)
project(stub_client VERSION 1.0.0)

# package management
include(cmake/conan.cmake)
conan_check()
conan_cmake_run(
    CONANFILE conanfile.txt
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing
)

# add dependencies
find_package(encore_common)

# client-specific libs
# TODO: seems like BW_LIBRARIES...
set(_libraries
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

# add executable sources
add_subdirectory(src/executable)