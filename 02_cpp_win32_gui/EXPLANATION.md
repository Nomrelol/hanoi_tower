# Tower of Hanoi - Native Win32 GUI Guide (Zero Third-Party Downloads!)

This guide explains the Native Windows GUI implementation in [main.cpp](file:///c:/Users/Dell/Desktop/proj/02_cpp_win32_gui/main.cpp).

> [!NOTE]
> **Key Feature**:
> - Creates a real graphical Windows Desktop GUI window **without downloading SFML or any 3rd-party library**.
> - Uses native Windows GDI API (`<windows.h>` + `g++ main.cpp -lgdi32 -mwindows`).
> - Uses a custom `struct RodStack` array stack (no STL containers) to meet teacher rules!

---

## How to Compile & Run
```bash
g++ main.cpp -o hanoi_gui.exe -lgdi32 -mwindows
.\hanoi_gui.exe
```
- `-lgdi32`: Links native Windows Graphics API built into every Windows machine.
- `-mwindows`: Hides command prompt background window.
