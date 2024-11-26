# Sudoku Solver

A Sudoku solver written in different programming languages.

## Index

- [Description](#description)
- [Features](#features)
- [Implemented Languages](#implemented-languages)
  - [C](#c)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#Installation)
- [Usage](#usage)
- [Contributions](#contributions)
- [License](#license)

## Description

This project is a Sudoku solver designed to compare implementations in different programming languages. Currently, the project includes an implementation in C, and versions in Rust and Zig are planned to be added.

## Features

- Solves Sudoku puzzles using the backtracking algorithm.
- Reads Sudoku boards from text files.
- Simple command-line interface.

## Implemented Languages

### C

The C version of the Sudoku solver is an efficient implementation that uses recursion and backtracking to find the solution.

#### Compilation and Execution

##### Prerequisites

- **CMake** (version 3.10 or higher)
- **GCC** or any other compiler compatible with C23

##### Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/gusvianadev/sudoku-solver
   ```
2. Navigate to the project directory:
    ```bash
    cd sudoku-solver/c
    ```
3. Create a build directory and generate the build files:
   ```bash
   mkdir build && cd build
   cmake ..
   ```
4. Compile the project:
   ```bash
   cmake --build .
   ```

##### Execution
Once compiled, you can run the Sudoku solver:
```bash
./sudoku-solver
```