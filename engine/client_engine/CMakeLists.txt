cmake_minimum_required(VERSION 3.12)
project(enCore VERSION 1.0.0)

# options
# only define options here so that they can be used inside each library
# it is responsibility of library to interpret option and target_compile_definition(...) for custom behavior
option(USE_NVAPI "Use NVIDIA sdk for frame analysis" OFF)
option(USE_TCMALLOC "Integrate tcmalloc for all allocation inside engine" ON)
option(ENABLE_TEXTURE_STREAMING "Stream in hi-res textures from disk" ON)
option(ENABLE_GEOMETRY_STREAMING "Stream in hi-res models from disk" ON)
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
conan_check()
conan_add_remote(NAME bincrafters URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_cmake_run(
    CONANFILE conanfile.py
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing
)

# List all libraries
# it is deliberate decision to not define pass-through CmakeLists.txt for "src" folder,
# because CMake is not like make or ninja. It does not need to traverse directories just for finding more targets.
# Keep this in alphabetic order for merge-tolerance
add_subdirectory(src/cstdmf)
add_subdirectory(src/resmgr)
#add_subdirectory(src/resmgr_v2)

# usefull targets for static and dynamic linking
file(WRITE ${CMAKE_BINARY_DIR}/encore_stub.cpp "")
add_library(encore_engine ${CMAKE_BINARY_DIR}/encore_stub.cpp)
target_link_libraries(encore_engine
    WG::cstdmf
    WG::resmgr
    CONAN_PKG::encore_common
)

if(WIN32)
    set_target_properties(encore_engine PROPERTIES
        LINK_FLAGS "/WHOLEARCHIVE"
    )
elseif(APPLE)
    set_target_properties(encore_engine PROPERTIES
        LINK_FLAGS "-Wl,-all_load"
    )
else()
    set_target_properties(encore_engine_static PROPERTIES
        LINK_FLAGS "-Wl,--whole-archive"
    )
endif()
# options defined at the top should rule which libraries will be included inside dll[s]
