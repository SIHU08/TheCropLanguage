cmake_minimum_required(VERSION 3.0)
project(TheCropProject VERSION 0.1.0)

add_executable(TheCropProject
    "main.cpp"
    src/utils.cpp
    src/parser/code.cpp
    src/parser/code_parser.cpp
)

set(CPACK_PROJECT_NAME crop)
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
