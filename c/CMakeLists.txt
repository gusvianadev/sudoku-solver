cmake_minimum_required(VERSION 3.12)
project(sudoku-solver)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
add_executable(sudoku-solver
    src/main.c
    src/helpers/prepare_sudokus.c
    src/helpers/solve_sudoku.c
    src/helpers/solve_cell.c
    src/helpers/print_sudoku.c
    src/helpers/print_cell.c
    src/helpers/walk.c
    src/helpers/quad_position.c
)

target_link_libraries(sudoku-solver m)
file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
