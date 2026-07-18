# N-Puzzle

A C++17 project for exploring search algorithms for the sliding-tile puzzle. The
project currently models a 3×3 puzzle state, calculates the Hamming-distance
heuristic, validates tile movements, and includes a custom minimum-priority queue
intended for informed search.

> [!NOTE]
> This repository is a work in progress. The public solver interface and search
> loop are not implemented yet, and the current sources contain compile errors.
> See [Project status](#project-status) for details.

## Planned algorithms

- A* search using Hamming distance as a heuristic
- Breadth-first search (BFS)

## Requirements

- A C++17-compatible compiler
- [CMake](https://cmake.org/) 3.9 or newer

The CMake configuration supports Windows and Unix-like systems. The library is
built with strict compiler warnings (`/W4 /WX` on MSVC and `-Wall -Werror` on
Unix-like systems).

## Build

From the repository root, configure and build the project:

```sh
cmake -S . -B build
cmake --build build
```

For multi-configuration generators such as Visual Studio, choose a configuration
when building:

```sh
cmake --build build --config Release
```

Build artifacts are written below `build/bin`, with a configuration subdirectory
when the selected generator uses one.

The build defines two targets:

- `n-puzzle` — the puzzle library
- `playground` — a small executable for experimenting with the library

Once the current compile errors are resolved, run the playground executable from
the generated binary directory. For example, with a Visual Studio Release build:

```powershell
.\build\bin\Release\playground.exe
```

## Current API

Include the main puzzle header and construct a state from a 3×3 matrix. The value
`0` represents the empty tile:

```cpp
#include <n-puzzle/N_Puzzle.h>

#include <vector>

int main()
{
    std::vector<std::vector<std::size_t>> tiles{
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8},
    };

    np::Puzzle puzzle{tiles};
}
```

The CMake target can be linked from another target in this source tree:

```cmake
target_link_libraries(your_target PRIVATE IsmailSamirIsmail::n-puzzle)
```

At present, puzzle movement and goal-checking methods are private, so constructing
and comparing states is the extent of the usable public puzzle API.

## Project structure

```text
.
├── CMakeLists.txt
├── n-puzzle/
│   ├── include/n-puzzle/    # Public library headers
│   └── src/n-puzzle/        # Library implementation
└── playground/
    └── src/playground.cpp   # Example executable
```

## Project status

The repository provides the beginnings of the puzzle model and priority queue,
but it is not yet a working solver. Known gaps include:

- fixing compilation errors in `N_Puzzle.cpp` and `Priority_Queue.cpp`;
- validating puzzle dimensions, tile values, and solvability;
- exposing a public solver API and returning the sequence of moves;
- implementing the A* and BFS search loops;
- supporting board sizes other than the currently fixed 3×3 layout;
- adding automated tests and a meaningful playground example.

## Contributing

Contributions are welcome. Please keep changes compatible with C++17 and add
tests for new puzzle behavior or search algorithms where possible.
