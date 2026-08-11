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
*A console prompt asks for disk count first, then the GUI window opens.*

---

## What the code does

1. **`struct Tower`** — array-based stack with `d[8]` and `top`. Same concept as `Rod` in `01-cpp-iostream` but with different field names (intentionally independent).

2. **`paint(HDC)`** — draws the full scene into a memory bitmap first (`CreateCompatibleDC`, `CreateCompatibleBitmap`) then copies it to screen in one `BitBlt` call — this removes flicker.

3. **`WndProc`** — Windows callback handling:
   - `WM_PAINT` → call `paint()`
   - `VK_SPACE` → start animation
   - `VK_UP` / `VK_DOWN` → adjust animation speed (+/- 100ms)

4. **`solve(hwnd, k, ...)`** — same recursive algorithm, but each `moveDisk` call redraws the window and calls `Sleep(delayMs)`.

5. **Input** — disk count is read via `cout/cin` in a temporary console (`AllocConsole`) before the window opens.

---

## Runtime Controls
| Key | Action |
|---|---|
| `SPACE` | Start animation |
| `↑` (Up arrow) | Speed up (−100ms) |
| `↓` (Down arrow) | Slow down (+100ms) |

---

## Teacher Viva Q&A

| Question | Answer |
|---|---|
| What is `WinMain`? | Windows entry point instead of `main()` when using `-mwindows` |
| What is double-buffering? | Drawing to an off-screen bitmap then copying avoids flicker |
| Why `TRANSPARENT` background mode? | So text drawn over coloured rectangles shows correctly |
| Why `-lgdi32`? | Links the GDI (Graphics Device Interface) system library for drawing |
