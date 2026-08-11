# 01-cpp-iostream

C++ console visualizer using only `#include <iostream>`. No platform-specific headers, no external libraries.

## Build
```powershell
g++ main.cpp -o bin/hanoi-iostream.exe
.\bin\hanoi-iostream.exe
```

## Design

**`struct Rod`** — array-based stack. `d[10]` holds disk sizes, `top` tracks the current height. `diskAt(lvl)` reads any position in the array, which the drawing function uses to render each level.

**`draw()`** — clears the screen by printing blank lines, then loops from the bottom level up, printing each rod's disk as `[===3===]` or a `|` for an empty slot.

**`solve(n, src, aux, dst)`** — standard recursive algorithm:
```
solve(n):
    if n == 1: move directly
    else:
        solve(n-1, src → aux)
        move src → dst
        solve(n-1, aux → dst)
```

**`wait()`** — spin loop using `volatile long long` to prevent compiler elimination. The user picks a speed level at startup; this avoids requiring `<windows.h>` or `<chrono>`.

## Notes

- `volatile` on the loop counter tells the compiler this variable has side effects and must not be optimized away, even though the loop body is empty.
- `diskAt(lvl)` is needed because `peek()` only reads the top. The draw function needs to read every level of the stack from bottom to top.
- Minimum moves for n disks: **2ⁿ − 1**
