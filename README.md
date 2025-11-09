# Sudoku Solver

A fast and efficient C++ implementation of a Sudoku puzzle solver using an optimized backtracking algorithm with the most-constrained-variable heuristic.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Algorithm](#algorithm)
- [Building the Project](#building-the-project)
- [Usage](#usage)
- [Input Format](#input-format)
- [Example](#example)
- [Technical Details](#technical-details)
- [Performance](#performance)

## Overview

This Sudoku solver can solve any valid 9x9 Sudoku puzzle using an intelligent backtracking algorithm. The solver reads puzzles from a text file, solves them, and displays both the original and solved puzzles.

## Features

- **Optimized Solving Algorithm**: Uses the most-constrained-variable (MCV) heuristic to minimize the search space
- **Fast Performance**: Dramatically reduces backtracking compared to naive approaches
- **Input Validation**: Checks for file errors and validates puzzle input
- **Clear Output**: Displays puzzles in an easy-to-read grid format with visual separators
- **Flexible Input**: Accepts 'x' or '0' for empty cells

## Algorithm

The solver uses **backtracking with constraint propagation** and the **most-constrained-variable heuristic**:

1. **Constraint Tracking**: Maintains hash sets for each row, column, and 3x3 box to track which numbers are already used
2. **Most-Constrained-Variable (MCV)**: At each step, selects the empty cell with the fewest possible valid values
3. **Early Failure Detection**: If any cell has zero possibilities, immediately backtracks
4. **Recursive Backtracking**: Tries valid values for the selected cell and recursively solves the rest

### Why This is Efficient

The MCV heuristic significantly reduces the search tree by:
- Trying cells that are more constrained first (higher chance of quick success or failure)
- Detecting invalid states early (before exploring deep into the recursion)
- Reducing the branching factor at each level of recursion

For example, choosing a cell with 2 possibilities instead of 7 can reduce the search space exponentially.

## Building the Project

### Prerequisites
- C++ compiler with C++20 support (g++, clang++)
- Make sure you have `g++` installed

### Build Steps

1. Clone or download the repository
2. Navigate to the project directory
3. Run the build script:

```bash
./make.sh
```

Or compile manually:

```bash
g++ -g --std=c++20 sudoku_solver.cpp -o sudoku_solver
```

## Usage

1. **Edit the input file** `sudoku_input.txt` with your puzzle (see format below)
2. **Run the solver**:
   ```bash
   ./sudoku_solver
   ```
3. **View the output** showing the original puzzle and the solution

## Input Format

The input file `sudoku_input.txt` should contain a 9x9 grid where:
- **Empty cells** are represented by `x` or `0`
- **Filled cells** contain digits `1-9`
- Cells can be separated by `|` for readability (optional)
- Whitespace and newlines are ignored

### Example Input Format

```
xxx|xxx|xxx
xxx|xxx|xxx
xxx|xxx|xxx
384|xxx|xxx
xxx|xxx|xxx
xxx|xxx|xxx
xxx|xxx|xxx
xxx|xxx|xxx
xxx|xxx|xx2
```

Or more compact:
```
xxxxxxxxx
xxxxxxxxx
xxxxxxxxx
384xxxxxx
xxxxxxxxx
xxxxxxxxx
xxxxxxxxx
xxxxxxxxx
xxxxxxxx2
```

## Example

### Input Puzzle:
```
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
---------------------
3 8 4 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
---------------------
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 2
```

### Output (Solved):
```
======SOLVED PUZZLE======

1 2 3 | 4 5 6 | 7 8 9
4 5 6 | 7 8 9 | 1 2 3
7 9 8 | 1 2 3 | 4 5 6
---------------------
3 8 4 | 2 1 5 | 6 9 7
2 1 5 | 6 9 7 | 3 4 8
6 7 9 | 3 4 8 | 2 1 5
---------------------
5 3 1 | 8 6 2 | 9 7 4
8 6 2 | 9 7 4 | 5 3 1
9 4 7 | 5 3 1 | 8 6 2
```

## Technical Details

### Data Structures

- **`plate[9][9]`**: 2D array storing the puzzle grid
- **`r[9]`**: Hash sets tracking used numbers in each row
- **`c[9]`**: Hash sets tracking used numbers in each column
- **`box[3][3]`**: Hash sets tracking used numbers in each 3x3 box

### Key Functions

- **`parsePlate()`**: Reads and parses the input file with error checking
- **`solvePlate()`**: Initializes constraint sets and starts the solver
- **`dfSearchOptimized()`**: Optimized backtracking with MCV heuristic
- **`check()`**: Validates if a number can be placed at a position
- **`countPossibilities()`**: Counts valid values for a cell (used in MCV)
- **`printPlate()`**: Displays the puzzle in formatted grid

### Algorithm Complexity

- **Time Complexity**: O(9^m) where m is the number of empty cells (much better than O(9^81) for naive backtracking due to MCV heuristic)
- **Space Complexity**: O(1) - constant space for the grid and constraint sets

## Performance

The optimized solver with MCV heuristic typically solves most puzzles in:
- **Easy puzzles**: < 1ms
- **Medium puzzles**: 1-10ms
- **Hard puzzles**: 10-100ms
- **Expert puzzles**: up to a few seconds

This is significantly faster than naive backtracking, which can take minutes or fail to solve hard puzzles in reasonable time.

## Bug Fixes and Improvements

Recent improvements include:
- Fixed `nextPlateIndex()` to correctly handle all cell transitions
- Fixed `parsePlate()` with proper loop conditions and cell counting
- Added input validation and error handling
- Implemented MCV heuristic for dramatic performance improvement
- Added support for '0' as empty cell marker
- Enhanced output formatting with grid separators

## License

This project is open source and available for educational purposes.
