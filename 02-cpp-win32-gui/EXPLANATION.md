# 02-cpp-win32-gui — Native Windows GUI Visualizer

**File**: [main.cpp](file:///c:/Users/Dell/Desktop/proj/02-cpp-win32-gui/main.cpp)

> [!NOTE]
> Uses **native Windows GDI** (`<windows.h>` only). Zero third-party downloads.  
> Compiles with `-lgdi32 -mwindows` — standard flags on every Windows MinGW install.

---

## Compile & Run
```powershell
cd 02-cpp-win32-gui
g++ main.cpp -o bin/hanoi-win32-gui.exe -lgdi32 -mwindows
.\bin\hanoi-win32-gui.exe
```

---

## Runtime Controls
| Key | Action |
|---|---|
| `1` – `8` | Select number of disks |
| `SPACE` | Start animation |
| `↑` | Speed up (−100ms) |
| `↓` | Slow down (+100ms) |
| `R` | Reset puzzle |

---

## What the code does

1. **`struct Tower`** — array-based stack with `d[8]` and `top = -1`.  
   Same push/pop concept as `Rod` in `01-cpp-iostream` but independently written with different field naming.

2. **`paint(HDC)`** — draws the full scene into a memory bitmap (`CreateCompatibleDC` + `CreateCompatibleBitmap`) then blits it to the screen in one `BitBlt` call — eliminates flicker.

3. **`WndProc`** — Windows message callback:
   - `WM_PAINT` → calls `paint()`
   - `WM_KEYDOWN` → handles 1–8 (disk select), SPACE (start), ↑/↓ (speed), R (reset)
   - `WM_DESTROY` → sets `g_hwnd = NULL` then calls `PostQuitMessage(0)`

4. **`g_hwnd` + `IsWindow()`** — a global window handle checked before every draw call inside `moveDisk`. If the user closes the window mid-animation, `solve()` detects it and stops immediately instead of crashing.

5. **`solve(k, src, aux, dst)`** — standard recursive Tower of Hanoi; each base-case move calls `moveDisk` which repaints and calls `Sleep(delayMs)`.

---

## Teacher Viva Q&A

| Question | Answer |
|---|---|
| What is `WinMain`? | Windows entry point instead of `main()` when using `-mwindows` |
| What is double-buffering? | Drawing to an off-screen bitmap then copying avoids screen flicker |
| Why `g_hwnd` global? | So `moveDisk` can safely check `IsWindow()` if the user closes mid-animation |
| Why `& ~WS_THICKFRAME`? | Removes the resize border so the window stays a fixed size |
| Why `-lgdi32`? | Links the GDI (Graphics Device Interface) system library for drawing |
