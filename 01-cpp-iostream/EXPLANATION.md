# 01-cpp-iostream — Pure C++ Console Visualizer

**File**: [main.cpp](file:///c:/Users/Dell/Desktop/proj/01-cpp-iostream/main.cpp)

> [!NOTE]
> **Only `#include <iostream>`** — zero other headers. No `<windows.h>`, no `<vector>`, no `<stack>`.  
> This is the teacher-safe version: trivial to compile anywhere, trivial to explain line by line.

---

## Compile & Run
```powershell
cd 01-cpp-iostream
g++ main.cpp -o bin/hanoi-iostream.exe
.\bin\hanoi-iostream.exe
```

---

## What the code does

1. **`struct Rod`** — a hand-built stack using `int d[10]` and `top = -1`.  
   - `push`, `pop`, `peek`, `diskAt` — four simple functions, each one line.  
   - No `std::stack`, no `std::vector`.

2. **`draw()`** — clears the screen by printing 35 blank lines (pure `cout`).  
   Loops from level 0 to level n, printing each rod's disk as `[===3===]` or a `|` for empty.

3. **`solve(n, src, aux, dst)`** — the classic three-line recursion:
   ```
   if n == 1 → move directly
   else → move n-1 to aux, move largest, move n-1 from aux to dst
   ```

4. **`wait()`** — a spin loop (`volatile long long`) for delay. Chosen by user at startup (fast / medium / slow).

---

## What the user sees at runtime
```
Enter number of disks (1-8): 3
Speed — 1=fast  2=medium  3=slow: 2
Press ENTER to start...
[display updates step by step]
SOLVED IN 7 MOVES!
```

---

## Teacher Viva Q&A

| Question | Answer |
|---|---|
| Why `volatile` in the delay loop? | Prevents the compiler from optimising the empty loop away |
| Why not use `Sleep()`? | `Sleep()` needs `<windows.h>` — this version is header-free |
| Why `diskAt(lvl)` instead of `peek()`? | `peek` only reads the top; `diskAt` reads any level for drawing |
| What is the minimum moves formula? | 2ⁿ − 1 (7 for n=3, 255 for n=8) |
