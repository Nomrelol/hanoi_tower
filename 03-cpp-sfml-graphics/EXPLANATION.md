# 03-cpp-sfml-graphics

Animated 2D visualizer using SFML. Each disk move is rendered as a three-phase smooth animation: lift, slide, drop.

## Build
```powershell
.\build.bat
.\bin\hanoi-sfml.exe
```

The script compiles with the correct `-I`/`-L` paths and copies the required DLLs to `bin/` automatically.

## Controls

| Key | Action |
|---|---|
| `1` – `8` | Select number of disks |
| `SPACE` or `ENTER` | Start solving |
| `↑` | Speed up (−50ms) |
| `↓` | Slow down (+50ms) |
| `R` | Reset |

## Design

**`struct Stack`** — array-based stack. Identical concept to the other modules.

**`renderScene(window, font)`** — draws the background, base platform, three rods, and all disks as `sf::RectangleShape` objects. Disk width scales with disk size; each disk is centered on its rod using `setOrigin`.

**`animateMove(...)`** — moves one disk in three phases, each timed by `sf::Clock`:
1. Lift straight up to a peak height above all rods
2. Slide horizontally to the target rod's X position
3. Drop down to the correct stack height

Each phase uses a `smoothstep` curve: `t² × (3 − 2t)`. This gives ease-in at the start and ease-out at the end, producing natural-looking motion.

**`solveHanoiSFML(...)`** — recursive solver that calls `animateMove` at each step instead of an instant stack swap.

## Notes

- SFML must be built for the same GCC version as the system compiler. MSVC-built SFML `.lib` files are not compatible with MinGW `g++` due to ABI differences.
- `smoothstep` is implemented inline; it does not require `<cmath>`.
- The window remains responsive during animation because `processEvents` is called inside each animation phase loop.
