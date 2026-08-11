# Tower of Hanoi - Windows Color Version Defense Guide

This guide explains the C++ Windows Color implementation in [main.cpp](file:///c:/Users/Dell/Desktop/proj/04-cpp-windows-color/main.cpp).

> [!NOTE]
> **Key Feature**: Uses `<windows.h>` for vibrant console colors (`SetConsoleTextAttribute`) and precise timing (`Sleep()`).
> - Custom `RodStack` struct (no STL containers used).

---

## How to Compile & Run
```powershell
g++ main.cpp -o bin/hanoi-win-color.exe
.\bin\hanoi-win-color.exe
```

---

## Code Highlights & Explanation
- **`setColor(int code)`**: Uses Windows API `SetConsoleTextAttribute()` to change text foreground color per disk size.
- **`Sleep(animationDelayMs)`**: Windows API function to pause between moves for animation.
- **`RodStack`**: Array `disks[10]` with `top` index. Custom `push()`, `pop()`, `peek()`.
