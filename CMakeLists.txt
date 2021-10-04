cmake_minimum_required(VERSION 3.0.0)
project(Roobik VERSION 0.1.0)

set(CMAKE_CPP_COMPILER g++-10)
set(CMAKE_CXX_COMPILER g++-10)
set(CMAKE_CXX_STANDARD 17)

# include(CTest)
# enable_testing()

set(SOURCES
    src/main.cpp
    src/cubiecube_utils.cpp
    src/utils.cpp
    src/Node.cpp
    src/ida.cpp
    src/CubieCube.cpp
    src/move_tables.cpp
)

add_executable(Roobik ${SOURCES})
target_include_directories(Roobik
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
set_property(TARGET Roobik PROPERTY CXX_STANDARD 17)
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
