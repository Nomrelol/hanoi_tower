# 03-cpp-sfml-graphics

Animated 2D visualizer using SFML. Each disk move is a three-phase animation: lift → slide → drop.

## Build
```powershell
.\build.bat
.\bin\hanoi-sfml.exe
```

## Controls

| Key | Action |
|---|---|
| `SPACE` | Start solving / Pause/Resume animation |
| Close button | Exit |

## Code Structure (~175 lines)

**`struct Stack`** — custom array-based stack with `push`, `pop`, `size`, `at`, `clear`. No `std::stack` used.

**`drawScene(win)`** — clears the window (black background), draws base platform, three rods, and stacked disks. Does NOT call `display()` — the caller handles that so animated disks can be drawn on top.

**`animateMove(win, src, dst)`** — moves one disk in three phases, each timed by `sf::Clock`:
1. Lift straight up above the rods
2. Slide horizontally to the target rod
3. Drop down to the correct stack height

Each phase uses linear interpolation: `position = start + (end - start) * progress`.

**`solve(win, n, src, aux, dst)`** — recursive solver. Calls `animateMove` at each step.

**`main()`** — asks for disk count via console, creates the SFML window, waits for SPACE to start, runs the solver, then keeps the window open.

