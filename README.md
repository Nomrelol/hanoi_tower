# Tower of Hanoi

A collection of five independent implementations of the **Tower of Hanoi** algorithm, each exploring a different rendering approach — from a pure standard-library console visualizer to a fully animated 2D graphics window.

---

## Implementations

```
├── 01-cpp-iostream/        C++ console visualizer  (stdlib only, no extra headers)
├── 02-cpp-win32-gui/       C++ native Windows GUI  (Win32 GDI, no third-party libs)
├── 03-cpp-sfml-graphics/   C++ animated 2D window  (SFML, automated build script)
├── 04-cpp-windows-color/   C++ color console       (Windows API color + Sleep)
└── 05-java-console/        Java console visualizer (custom stack, no java.util.Stack)
```

Each module is self-contained: its own source file, its own `bin/` output directory, and its own `EXPLANATION.md`.

---

## Data Structure

Every implementation builds its own array-based stack from scratch — no standard container libraries (`std::stack`, `std::vector`, `java.util.Stack`) are used anywhere.

| Module | Stack Type | Array Field | Read Method |
|---|---|---|---|
| `01-cpp-iostream` | `struct Rod` | `d[10]` | `diskAt(lvl)` |
| `02-cpp-win32-gui` | `struct Tower` | `d[8]` | `at(lvl)` |
| `03-cpp-sfml-graphics` | `struct Stack` | `arr[8]` | `getAt(lvl)` |
| `04-cpp-windows-color` | `struct Peg` | `d[10]` | `diskAt(lvl)` |
| `05-java-console` | `class Peg` (inner) | `disk[]` | `get(i)` |

---

## How to Build & Run

### 01 — C++ Standard Library Only
```powershell
cd 01-cpp-iostream
g++ main.cpp -o bin/hanoi-iostream.exe
.\bin\hanoi-iostream.exe
```

### 02 — Native Windows GUI
```powershell
cd 02-cpp-win32-gui
g++ main.cpp -o bin/hanoi-win32-gui.exe -lgdi32 -mwindows
.\bin\hanoi-win32-gui.exe
```

### 03 — SFML 2D Animated Window
```powershell
cd 03-cpp-sfml-graphics
.\build.bat
.\bin\hanoi-sfml.exe
```

### 04 — Windows Color Console
```powershell
cd 04-cpp-windows-color
g++ main.cpp -o bin/hanoi-win-color.exe
.\bin\hanoi-win-color.exe
```

### 05 — Java Console
```powershell
cd 05-java-console
javac -d bin TowerOfHanoi.java
java -cp bin TowerOfHanoi
```

---

## Requirements

- **C++ modules**: MinGW GCC (`g++` on PATH)
- **SFML module**: GCC-built SFML 2.6 already placed in `03-cpp-sfml-graphics/SFML/`
- **Java module**: JDK 8 or later
