# This project stuff is only needed if we want
# to have a separate delivery cycle for it (external to engine?)
cmake_minimum_required(VERSION 3.10)
project(resmgr VERSION 1.0)
# add all sources without custom variables
# do not define any custom var for shared\static lib
# cmake is intelegent enough for providing BUILD_SHARED_LIBS option
# for specific cases you can define your engine_wrapper like all others,
# but all wrapped libraries as STATIC only, because circular dependencies and stuff
add_library(resmgr
    res_management.cpp # even for header-only provide simple cpp for good c++ tooling support
    include/resmgr/res_management.hpp
    factory.cpp
    include/resmgr/factory.hpp
    reloadable.cpp
    include/resmgr/reloadable.hpp
)
# this is public library so it defines include directory for self and others
# most of the time you need only 1 include directory, all other include directories will come from linked targets
# inside include directory always create <lib_name> directory for nice #include "<lib_name>/<header.hpp>"
# this generator expressions used for install\build logic
# it is most generic case, so dont touch it
target_include_directories(resmgr PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
# explicitly say that this library needs and supports c++17
# any other features I personaly dont find usefull, but you can add them as well
# cxx_constepr and such
target_compile_features(resmgr PUBLIC cxx_std_17)


### DEPENDENCY definition ###
# this is more generic style for CMake
# vanilla style of dependency management through find_package
# it has to have right CMAKE_MODULE_PATH to have all FindXXX.cmake scripts
# this scripts has to define appropriate targets (Boost::Boost for this example)
find_package(Boost 1.68 REQUIRED)
# linking is most crucial part of CMake target system to work
# all features and PUBLIC (transitive) dependencies are added to this library
# so dont abuse you build by PUBLICaly linking all of the things
# always think why you need each library for
target_link_libraries(resmgr
    PUBLIC
        WG::cstdmf # this is right way of linking your libraries, do not use namespace-less lib
    PRIVATE
        Boost::Boost # this library comes from package manager, so it has this namespace
)
# We need to add namespaced alias target to not confuse CMake linking
# without namespace cmake will try to find our library inside LD= and other places
# it may be very confusing for cmake and too much sloooow...
# so always link with namespaced modern targets (like WOT::cstdmf up there)
add_library(WG::resmgr ALIAS resmgr)


### ALTERNATIVE DEPENDENCIES ###
# alternative style is to use conans basic_setup(targets)
# so that conan will provide all nessesary CONAN_PKG:: namespaced imported targets
# Consider: NO find_package()!
# this will not work nice with INSTALL, because of find_dependency and stuff
# so maybe we can do not INSTALL libs, this will remove so much boilerplate
# but maybe will not play nice in long-term maintance
#target_link_libraries(resmgr
#    PUBLIC
#        WG::cstdmf
#    PRIVATE:
#        CONAN_PKG::boost
#)


### INSTALL ZONE ###
# TODO: how we can avoid this repetitive boilerplate for every library?
# be a better guy and define install requirements
# here goes some boilerplate for cutting edge install directives
install(
    TARGETS resmgr EXPORT resmgrTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(
    EXPORT resmgrTargets
    DESTINATION lib/cmake/resmgr
    FILE resmgrTargets.cmake
    NAMESPACE WG::
)
install(
    DIRECTORY include/resmgr
    DESTINATION include
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(resmgrConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)
# TODO: I personaly dont get it yet why we need this resmgrConfig.cmake:
# include(CMakeFindDependencyMacro)
# find_dependency(MyDep 1.0)
# include(${CMAKE_CURRENT_LIST_DIR}/resmgrTargets.cmake)
#
# what find_dependency macro do? How to adapt it for conan stuff...
install(FILES
#        resmgrConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/resmgrConfigVersion.cmake
    DESTINATION lib/cmake/resmgr)

### TESTING ###
add_subdirectory(test)
