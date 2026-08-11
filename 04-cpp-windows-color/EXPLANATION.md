# 04-cpp-windows-color — Windows Colorful Console Visualizer

**File**: [main.cpp](file:///c:/Users/Dell/Desktop/proj/04-cpp-windows-color/main.cpp)

> [!NOTE]
> Uses `<windows.h>` for `SetConsoleTextAttribute` (colored text) and `Sleep` (delay).  
> No third-party library — works out of the box on any Windows machine.

---

## Compile & Run
```powershell
cd 04-cpp-windows-color
g++ main.cpp -o bin/hanoi-win-color.exe
.\bin\hanoi-win-color.exe
```

---

## What the code does

1. **`struct Peg`** — array-based stack using `d[10]` and `top = -1`.  
   Fields and method names are intentionally different from the other versions (`d` instead of `arr`, `diskAt` instead of `getAt`, etc.).

2. **`color(int c)`** — calls `SetConsoleTextAttribute` to change the terminal text colour. Windows console color codes go from 0 (black) to 15 (white); codes 9–14 give bright colours per disk.

3. **`draw()`** — calls `system("cls")` to clear, then loops over each disk level and rod, printing coloured disk shapes `<===3===>` using `color()` + `cout`.

4. **Speed selection** — user picks 1 (fast: 200ms), 2 (medium: 500ms), or 3 (slow: 900ms) at startup.

5. **`solve(k, src, aux, dst)`** — standard Tower of Hanoi recursion, calling `move()` at the base case.

---

## Teacher Viva Q&A

| Question | Answer |
|---|---|
| What is `SetConsoleTextAttribute`? | A Windows API function that changes the foreground/background colour of console text |
| Why `system("cls")`? | Clears the terminal screen between steps to simulate animation |
| What does color code `14` mean? | Bright yellow (Windows console palette) |
| Why `volatile` is NOT needed here? | We use `Sleep()` instead of a spin loop, so the compiler can't optimize it away |
