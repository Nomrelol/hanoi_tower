# 02-cpp-win32-gui

Native Windows GUI visualizer using Win32 GDI. No third-party libraries required.

## Build
```powershell
g++ main.cpp -o bin/hanoi-win32-gui.exe -lgdi32 -mwindows
.\bin\hanoi-win32-gui.exe
```

## Controls

| Key | Action |
|---|---|
| `1` – `8` | Select number of disks |
| `SPACE` | Start animation |
| `↑` | Speed up (−100ms per step) |
| `↓` | Slow down (+100ms per step) |
| `R` | Reset |

## Design

**`struct Tower`** — array-based stack. Same push/pop/at pattern as the other modules.

**`paint(HDC)`** — renders into an off-screen memory bitmap using `CreateCompatibleDC` + `CreateCompatibleBitmap`, then copies to the screen in one `BitBlt` call. This double-buffering prevents flicker during animation.

**`WndProc`** — standard Windows message procedure. Handles `WM_PAINT`, `WM_KEYDOWN`, and `WM_DESTROY`. On destroy, sets `g_hwnd = NULL` before posting the quit message.

**`g_hwnd` + `IsWindow()`** — the global handle is checked with `IsWindow()` before every repaint inside the animation loop. If the window is closed while the solver is running, animation stops cleanly rather than crashing on a dangling handle.

**`solve(k, src, aux, dst)`** — recursive Tower of Hanoi. Each disk move calls `moveDisk`, which repaints the window and sleeps for `delayMs` milliseconds.

## Notes

- `WinMain` is the entry point for GUI subsystem builds (`-mwindows`). It replaces the standard `main()`.
- `-lgdi32` links the Windows Graphics Device Interface library, which provides `CreateCompatibleDC`, `BitBlt`, `FillRect`, etc.
- `& ~WS_THICKFRAME & ~WS_MAXIMIZEBOX` removes the resize and maximize controls so the window stays a fixed size.
