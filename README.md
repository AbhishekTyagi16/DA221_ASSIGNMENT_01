# DA221 Assignment 01 — 8-Puzzle Solver (A\* + Heuristics + HTML Visualizer)

A complete **C++17** implementation of the **8-puzzle** using **A\*** search with three heuristics and a simple **browser visualizer**.

## Features

- Generates **10 random solvable** 8-puzzle instances.
- Solves each instance using A\* with:
  - **Misplaced Tiles**
  - **Manhattan Distance**
  - **Custom Heuristic:** Manhattan + Linear Conflict (admissible)
- Prints:
  - Each instance grid.
  - **Two sample solutions** step-by-step (depth ≥ 10).
  - A summary table of performance metrics.
- Exports the two sample solutions as JSON for visualization in `web/viewer.html`.

---

## Project Structure

```text
DA221_ASSIGNMENT01/
├── include/
│   ├── astar.h
│   ├── check_solvable.h
│   ├── export_json.h
│   ├── heuristics.h
│   ├── instances.h
│   ├── puzzle_generator.h
│   ├── puzzle_state.h
│   └── results.h
├── src/
│   ├── astar.cpp
│   ├── check_solvable.cpp
│   ├── export_json.cpp
│   ├── heuristics.cpp
│   ├── instances.cpp
│   ├── main.cpp
│   ├── puzzle_generator.cpp
│   ├── puzzle_state.cpp
│   └── results.cpp
├── out/
│   ├── sol_sample1.json
│   └── sol_sample2.json
├── web/
│   └── viewer.html
├── README.md
└── 8puzzle.exe  (optional build output)
```

---

## Requirements

- C++17 compiler (tested with `g++`)
- Optional (for local web server mode): Python 3

---

## Build & Run

### Windows (PowerShell)

From the project root:

```powershell
g++ -std=c++17 -Iinclude src\*.cpp -O2 -o 8puzzle.exe
.\8puzzle.exe
```

If PowerShell doesn't expand `src\*.cpp`, use:

```powershell
g++ -std=c++17 -Iinclude (Get-ChildItem src\*.cpp | % Name) -O2 -o 8puzzle.exe
.\8puzzle.exe
```

### Linux / macOS

```bash
g++ -std=c++17 -Iinclude src/*.cpp -O2 -o 8puzzle
./8puzzle
```

---

## Output

For each of the 10 instances, the program runs A\* with all three heuristics and collects:

| Metric     | Description                                    |
| ---------- | ---------------------------------------------- |
| `Time(ms)` | Runtime in milliseconds                        |
| `SolLen`   | Optimal solution length (number of moves)      |
| `Popped`   | Number of nodes popped from the priority queue |
| `Expanded` | Number of states actually expanded             |

A summary table is printed at the end. Two sample solutions (depth ≥ 10) are printed step-by-step.

---

## Visualizer (HTML)

Two sample Manhattan solutions are exported to:

- `out/sol_sample1.json`
- `out/sol_sample2.json`

### Open the visualizer (no server needed)

1. Run the program to generate the JSON files.
2. Open `web/viewer.html` in your browser.
3. Use the file picker on the page to load one of the JSON files.

### Optional: run a local server (recommended)

From the project root:

**Windows:**

```dos
py -m http.server 8000
```

**Linux/macOS:**

```bash
python3 -m http.server 8000
```

Then open: [http://localhost:8000/web/viewer.html](http://localhost:8000/web/viewer.html)

---

## Implementation Overview

### 1. State Representation (`puzzle_state`)

The board is stored in row-major order as 9 values (`0` represents the blank). `neighbors()` generates valid moves by swapping the blank with adjacent tiles. Hashing and equality operators allow using states in `unordered_map`.

### 2. Solvability Check (`check_solvable`)

Uses standard inversion parity for 3×3 puzzles — counts inversions ignoring `0` (the blank). A state is solvable if and only if the inversion parity of the start state equals that of the goal state.

### 3. A\* Search (`astar`)

Priority queue ordered by `f(n) = g(n) + h(n)`. Tracks runtime and search statistics, and reconstructs the optimal path using parent pointers.

### 4. Heuristics (`heuristics`)

- **Misplaced Tiles:** counts tiles not in their goal position (excluding blank).
- **Manhattan Distance:** sum of per-tile distances to their goal positions.
- **Custom:** Manhattan + Linear Conflict (remains admissible).

Expected performance trend: Misplaced expands the most nodes → Manhattan expands fewer → Custom expands the fewest.

---

## File Guide

| Path                  | Description                                                                 |
| --------------------- | --------------------------------------------------------------------------- |
| `include/`            | Header files                                                                |
| `src/`                | Implementation files                                                        |
| `src/main.cpp`        | Runs experiments, prints two sample solutions, exports JSON, prints summary |
| `src/export_json.cpp` | Exports solution path to JSON                                               |
| `web/viewer.html`     | Loads JSON and animates the puzzle                                          |
| `out/`                | Generated JSON outputs                                                      |

---

## Troubleshooting

### `*.cpp: Invalid argument` in PowerShell

Use the modified build command:

```powershell
g++ -std=c++17 -Iinclude (Get-ChildItem src\*.cpp | % Name) -O2 -o 8puzzle.exe
```

### Getting `SolLen = -1`

This usually means an unsolvable instance slipped through. Ensure `check_solvable.cpp` counts inversions correctly — the condition should be `v[i] > v[j]` with `i < j`, and it must explicitly ignore the blank (`0`).

---

## License

Academic / assignment use.
