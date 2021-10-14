cmake_minimum_required(VERSION 3.0.0)
project(Roobik VERSION 0.1.0)

set(CMAKE_CPP_COMPILER g++-10)
set(CMAKE_CXX_COMPILER g++-10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -pthread -mcmodel=large")

# include(CTest)
# enable_testing()

set(SOURCES
    src/main.cpp
    src/kociemba.cpp
    src/CoordCube.cpp
    src/move_tables.cpp
    src/heuristics.cpp
    src/solver.cpp
    src/cubiecube_utils.cpp
    src/utils.cpp
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
