# Tower of Hanoi - Native Win32 GUI Guide (Zero Third-Party Downloads!)

This guide explains the Native Windows GUI implementation in [main.cpp](file:///c:/Users/Dell/Desktop/proj/02-cpp-win32-gui/main.cpp).

> [!NOTE]
> **Key Feature**:
> - Creates a real graphical Windows Desktop GUI window **without downloading SFML or any 3rd-party library**.
> - Uses native Windows GDI API (`<windows.h>` + `g++ main.cpp -o bin/hanoi-win32-gui.exe -lgdi32 -mwindows`).
> - Uses a custom `struct RodStack` array stack (no STL containers) to meet teacher rules!

---

## How to Compile & Run
```powershell
g++ main.cpp -o bin/hanoi-win32-gui.exe -lgdi32 -mwindows
.\bin\hanoi-win32-gui.exe
```
- `-lgdi32`: Links native Windows Graphics API built into every Windows machine.
- `-mwindows`: Hides command prompt background window.

---

## Code Breakdown for Oral Defense
- **Double-Buffering (`BitBlt`)**: Renders scenes onto an off-screen memory bitmap buffer first, then copies it to the display window to eliminate window flicker.
- **`RodStack`**: Custom array stack (`disks[8]`) with `push`, `pop`, `peek`, and `getDiskAt` methods.
- **`WinMain`**: Standard entry point for Windows GUI applications.
