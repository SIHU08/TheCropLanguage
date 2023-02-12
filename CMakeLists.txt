cmake_minimum_required(VERSION 3.22)
project(crop VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

add_executable(cropc main.cpp)

target_link_libraries(cropc ${CMAKE_DL_LIBS})
target_compile_features(cropc PRIVATE cxx_std_17)

add_subdirectory(addons)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)