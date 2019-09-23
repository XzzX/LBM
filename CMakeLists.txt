cmake_minimum_required(VERSION 3.5)

set (CMAKE_CXX_STANDARD 14)

project(LBM)
add_executable(${PROJECT_NAME} "Main.cpp" "LB.cpp" "BoundaryConditions.cpp")
target_compile_options(LBM PUBLIC -Wall -Wextra -Werror)

