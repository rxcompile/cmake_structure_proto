cmake_minimum_required(VERSION 3.10)
project(enCore VERSION 1.0.0)

# options
# only define options here so that they can be used inside each library
# it is responsibility of library to interpret option and target_compile_definition(...) for custom behavior
option(USE_NVAPI "Use NVIDIA sdk for frame analysis" OFF)
option(USE_TCMALLOC "Integrate tcmalloc for all allocation inside engine" ON)
option(ENABLE_TEXTURE_STREAMING "Stream in hi-res textures from disk" ON)
option(ENABLE_GEOMETRY_STREAMING "Strean in hi-res models from disk" ON)
option(ENABLE_REFLECTION "Add reflection info inside engine classes" OFF) # see "reflection" lib
option(ENABLE_UNIT_TESTING "Unit test engine" OFF)

# CMake configuration
if(ENABLE_UNIT_TESTING)
    enable_testing()
endif()
enable_language(CXX)
cmake_policy(SET CMP0074 OLD)

# package management
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/memsharded/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/develop/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(
    REQUIRES
        boost/1.68.0@conan/stable
        gtest/1.8.0@conan/stable
    BASIC_SETUP
    BUILD missing
    )

# List all libraries
# it is deliberate decision to not define pass-through CmakeLists.txt for "src" folder,
# because CMake is not like make or ninja. It does not need to traverse directories just for finding more targets.
# Keep this in alphabetic order for merge-tolerance
add_subdirectory(src/cstdmf)
add_subdirectory(src/resmgr)
# add_subdirectory(src/resmgr_v2)
