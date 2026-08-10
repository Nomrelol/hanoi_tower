# Tower of Hanoi - SFML 2D Graphics Animation Guide

This guide explains the 2D Graphical SFML implementation in [main.cpp](file:///c:/Users/Dell/Desktop/proj/03_cpp_sfml_graphics/main.cpp).

> [!NOTE]
> **Key Features**:
> - Renders a GUI window (900x600) using SFML Graphics (`sf::RenderWindow`, `sf::RectangleShape`).
> - **Smooth 3-Phase Animation**: Disks lift upwards, slide horizontally, and drop down onto target rods.
> - **Custom Stack Data Structure**: Uses `struct Stack` (array + `top` pointer). **No STL containers used** to meet teacher rules!

---

## How to Set Up & Compile

1. Paste your downloaded `SFML` folder directly inside this `03_cpp_sfml_graphics/` directory so it looks like:
   ```text
   03_cpp_sfml_graphics/
   ├── SFML/
   │   ├── include/ (contains SFML/Graphics.hpp)
   │   ├── lib/     (contains libsfml-graphics.a)
   │   └── bin/     (contains sfml-graphics-2.dll)
   ├── main.cpp
   ├── build.bat
   └── EXPLANATION.md
   ```
2. Double-click `build.bat` or run:
   ```powershell
   .\build.bat
   ```
3. Run `.\hanoi.exe`!
