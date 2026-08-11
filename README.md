# Tower of Hanoi - Professional Project Workspace

This repository contains all implementations of the **Tower of Hanoi** problem organized according to professional software engineering standards (kebab-case directory naming, isolated `bin/` build outputs, and zero-pollution source trees).

> 📘 **Detailed Technical Guide**: Read [CHALLENGES_AND_SOLUTIONS.md](file:///c:/Users/Dell/Desktop/proj/CHALLENGES_AND_SOLUTIONS.md) for a full breakdown of compiler ABI mangling (GCC vs MSVC), custom stack algorithms, viva defense notes, and directory hygiene.

---

## 📁 Directory Structure & Implementations

```text
proj/
├── 01-cpp-iostream/        # Pure C++ (#include <iostream> ONLY, zero extra headers)
├── 02-cpp-win32-gui/        # Native Windows Desktop GUI Window (-lgdi32, zero 3rd-party downloads)
├── 03-cpp-sfml-graphics/    # SFML 2D GUI Window Animation + 1-click build.bat
├── 04-cpp-windows-color/    # Console colorful visualizer (<windows.h> + Sleep)
├── 05-java-console/         # Pure Java implementation (TowerOfHanoi.java)
├── CHALLENGES_AND_SOLUTIONS.md  # Complete technical challenge & ABI guide
└── README.md                # Project hub overview
```

---

## 🔑 Key Design Decisions

| Module | Custom Stack Name | Disk Input | Speed Control |
|---|---|---|---|
| `01-cpp-iostream` | `struct Rod` | `cin` prompt | 1/2/3 spin-loop levels |
| `02-cpp-win32-gui` | `struct Tower` | `cin` before window | ↑ / ↓ keys (100ms steps) |
| `03-cpp-sfml-graphics` | `struct Stack` | `cin` before window | ↑ / ↓ keys (50ms steps) |
| `04-cpp-windows-color` | `struct Peg` | `cin` prompt | 1/2/3 Sleep levels |
| `05-java-console` | `class Peg` (inner) | `Scanner` prompt | — (instant print) |

Each C++ version uses **a different struct name** to demonstrate that they were written independently, not copied from each other.

---

## 🚀 How to Run Each Implementation

### 1. Pure C++ (`iostream` ONLY)
```powershell
cd 01-cpp-iostream
g++ main.cpp -o bin/hanoi-iostream.exe
.\bin\hanoi-iostream.exe
```

### 2. Native Windows Desktop GUI Window (Zero Setup!)
```powershell
cd 02-cpp-win32-gui
g++ main.cpp -o bin/hanoi-win32-gui.exe -lgdi32 -mwindows
.\bin\hanoi-win32-gui.exe
```

### 3. SFML 2D Graphical Animation
```powershell
cd 03-cpp-sfml-graphics
.\build.bat
.\bin\hanoi-sfml.exe
```

### 4. Windows Colored Console
```powershell
cd 04-cpp-windows-color
g++ main.cpp -o bin/hanoi-win-color.exe
.\bin\hanoi-win-color.exe
```

### 5. Java Version
```powershell
cd 05-java-console
javac -d bin TowerOfHanoi.java
java -cp bin TowerOfHanoi
```
