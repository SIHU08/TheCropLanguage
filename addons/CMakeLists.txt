cmake_minimum_required(VERSION 3.16)
project(crop VERSION 0.1.0)

include_directories(include/)

add_library(addon_interpret SHARED
    interpret/interpretaddon.cpp
    interpret/utils.cpp
    interpret/variables.cpp)
target_compile_features(addon_interpret PRIVATE cxx_std_17)
target_include_directories(addon_interpret PRIVATE interpret/include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
