# N-Puzzle

N-Puzzle is a work-in-progress C++17 library for sliding-tile puzzle search. It
currently contains the beginnings of a fixed 3×3 puzzle-state model, a Hamming
distance heuristic, and a custom minimum-priority queue. The intended search
algorithms are breadth-first search (BFS) and A*.

> [!IMPORTANT]
> The project builds, but it is not a working solver yet. There is no public
> solver API or implemented search loop. The commands and API below describe the
> currently supported project layout.

## Puzzle model

The current model has these fixed rules:

- Boards are 3×3 (`np::WIDTH == 3` and `np::HEIGHT == 3`).
- `0` represents the empty space.
- The goal state is `1, 2, 3, 4, 5, 6, 7, 8, 0` in row-major order.
- Hamming distance counts misplaced non-zero tiles.
- Internally, `UP`, `DOWN`, `LEFT`, and `RIGHT` describe movement of the empty
  space. Movement is not part of the public API yet.

Board sizes other than 3×3 are not supported. Generalizing the state model to
N×N boards is possible future work, not current behavior.

## Requirements

- A C++17-compatible compiler
- [CMake](https://cmake.org/) 3.9 or newer

CMake disables compiler-specific C++ extensions. Both targets enable strict
warnings and treat them as errors: `/W4 /WX` with MSVC and `-Wall -Werror` on
Unix-like systems.

## Configure and build

From the repository root, configure and build with:

```sh
cmake -S . -B build
cmake --build build
```

For a multi-configuration generator such as Visual Studio, select a
configuration explicitly:

```sh
cmake --build build --config Debug
cmake --build build --config Release
```

Build artifacts are placed below `build/bin`, with a configuration subdirectory
when the generator uses one.

The project defines these targets:

- `n-puzzle` — the library
- `playground` — a small executable linked to the library
- `IsmailSamirIsmail::n-puzzle` — an alias for the library target

Both targets compile as C++17 with warnings treated as errors. The priority queue
still has behavioral limitations that are tracked separately from build support.

## Current public API

The only meaningful public operation is constructing and comparing fixed-size
puzzle states. Include the main header and pass a 3×3 matrix:

```cpp
#include <cstddef>
#include <vector>

#include <n-puzzle/N_Puzzle.h>

int main()
{
    const std::vector<std::vector<std::size_t>> tiles{
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8},
    };

    const np::Puzzle puzzle{tiles};
}
```

To consume the library from another target in this source tree:

```cmake
target_link_libraries(your_target PRIVATE IsmailSamirIsmail::n-puzzle)
```

Important current limitations:

- Construction does not validate matrix dimensions, tile range, uniqueness, or
  solvability. Callers must not rely on malformed input being rejected.
- Goal checks, Hamming distance, movement, and board inspection are private.
- There is no BFS or A* entry point.
- There is no solution-result type or sequence-of-moves result.
- Direction semantics are internal and may not be used through the public API.

## Playground

The `playground` target is currently only a placeholder. Its example constructs
an invalid all-zero board and prints `Hello, World!`; it does not solve or display
a puzzle. A multi-configuration build places the Debug executable at:

```powershell
.\build\bin\Debug\playground.exe
```

An end-to-end solver example is tracked as separate future work.

## Tests

There is currently no automated test target and no CTest suite, so a successful
build must not be reported as passing tests. After code changes, configure and
build the project, treat compiler warnings as failures, and run `playground` only
when it meaningfully exercises the changed behavior.

Automated coverage for validation, movement, state identity, the priority queue,
BFS, and A* remains future work.

## Project structure

```text
.
├── CMakeLists.txt
├── n-puzzle/
│   ├── CMakeLists.txt
│   ├── include/n-puzzle/    # Public library headers
│   └── src/n-puzzle/        # Library implementation
├── playground/
│   ├── CMakeLists.txt
│   └── src/playground.cpp   # Placeholder executable
└── README.md
```

## Implementation status

The repository is an early implementation and intentionally remains scoped to
3×3 boards. Outstanding work includes:

- correcting the remaining behavioral limitations in the priority queue;
- validating dimensions, tile values, uniqueness, and solvability;
- exposing a safe public state and movement API;
- implementing BFS and A* with a documented solution result;
- adding automated tests and a meaningful playground example; and
- optionally generalizing the model beyond 3×3 after the fixed-size solver is
  complete.

## Contributing

Keep changes compatible with standard C++17, preserve the `np` namespace and
public include layout, and avoid compiler-specific language extensions. Once a
test target exists, add or update focused tests for new behavior.
