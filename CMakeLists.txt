cmake_minimum_required(VERSION 3.12)
project(meta_project VERSION 1.0.0)

set(A_TARGET_PROJECT CACHE STRING "Target project you want to work on")
set_property(CACHE A_TARGET_PROJECT PROPERTY
    STRINGS
    Client Server Common)
message(STATUS "Target project specified as ${A_TARGET_PROJECT}")

if(A_TARGET_PROJECT STREQUAL Client)
    add_subdirectory(programming/client)
elseif(A_TARGET_PROJECT STREQUAL Server)
    add_subdirectory(programming/server)
elseif(A_TARGET_PROJECT STREQUAL Common)
    add_subdirectory(programming/common)
else()
    message(WARNING "TARGET_PROJECT should be specified as Client, Server or Common")
endif()
