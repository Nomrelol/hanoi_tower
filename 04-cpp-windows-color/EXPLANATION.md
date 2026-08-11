# 04-cpp-windows-color

Color console visualizer using Windows API. Each disk is printed in a distinct color using `SetConsoleTextAttribute`.

## Build
```powershell
g++ main.cpp -o bin/hanoi-win-color.exe
.\bin\hanoi-win-color.exe
```

## Design

**`struct Peg`** — array-based stack. `d[10]` stores disk sizes, `top` tracks the height. `diskAt(lvl)` reads any level for rendering.

**`color(int c)`** — wraps `SetConsoleTextAttribute`. Windows console color codes 0–15 map to specific colors; codes 9–14 are the bright variants used for the disks.

**`draw()`** — clears with `system("cls")`, then loops over each level from top to bottom. For each rod at that level, it prints a disk shape `<===3===>` in the corresponding color, or a `|` for an empty slot.

**`solve(k, src, aux, dst)`** — standard recursive algorithm. `move()` pops from the source, pushes to the destination, increments the step counter, and calls `draw()` followed by `Sleep(delayMs)`.

## Notes

- `system("cls")` is used to clear the screen between steps, producing a step-by-step animation effect in the terminal.
- `Sleep()` comes from `<windows.h>` and pauses the process for an exact millisecond count, unlike the spin-loop approach in `01-cpp-iostream`.
- Color code `14` is bright yellow; code `10` is bright green; code `11` is bright cyan.
