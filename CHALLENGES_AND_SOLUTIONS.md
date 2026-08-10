# Tower of Hanoi - Technical Challenges, Solutions & Professional Architecture Guide

This comprehensive guide documents all technical challenges faced, teacher constraints enforced, design decisions made, and professional software architecture patterns implemented in this repository.

---

## 🎯 Background & Project Goals

The objective of this assignment was to implement and graphically demonstrate the **Tower of Hanoi** puzzle in C++ (and Java).

Key requirements & constraints:
1. **Rule Enforcement**: Disks of decreasing size start on Rod A. Only one disk may be moved at a time, and a larger disk can never be placed on top of a smaller disk.
2. **Strict Teacher Restriction**: **NO standard STL container libraries** (`<vector>`, `<stack>`, `<queue>`, `<list>`). All data structures must be built from scratch.
3. **Code Defense Readiness**: Code must be readable, student-friendly, and easy to explain line-by-line during teacher viva / oral exams.
4. **Graphical Demonstration**: Explore multiple visual representation methods (pure terminal, ANSI/Windows color console, native Win32 GUI window, and 3rd-party 2D SFML graphics).

---

## 🛠️ Challenges & Solutions Matrix

### Challenge 1: Implementing Rod Stacks without STL Containers
* **The Problem**: Standard implementations rely on `std::stack` or `std::vector`. The teacher explicitly prohibited helper libraries.
* **Our Solution**:
  We engineered a custom array-based stack (`struct Stack` / `RodStack`) built from scratch:
  ```cpp
  struct Stack {
      int arr[10];  // Storage array for disk sizes
      int top = -1; // -1 indicates empty stack

      void push(int disk) { arr[++top] = disk; }
      int pop() { return (top == -1) ? 0 : arr[top--]; }
      int peek() { return (top == -1) ? 0 : arr[top]; }
      bool isEmpty() { return top == -1; }
      int getAt(int level) { return (level <= top) ? arr[level] : 0; }
  };
  ```
* **Why it works**: It is 100% compliant with the teacher's rules, has \(O(1)\) push/pop efficiency, and takes 30 seconds to explain during a viva.

---

### Challenge 2: Avoiding Over-Engineered "AI-looking" Code for Oral Defense
* **The Problem**: Complex GUI boilerplate code (`WNDCLASS`, `HWND`, `LRESULT`, window message loops) raises academic suspicion and is hard for a student to explain line-by-line.
* **Our Solution**:
  Created **`01-cpp-iostream/`**.
  - Contains **ONLY `#include <iostream>`** — zero external headers.
  - Screen refresh handled via `cout` newlines.
  - Delay timing handled via a simple `for` spin loop.
  - Accompanied by a detailed `EXPLANATION.md` viva cheat sheet.

---

### Challenge 3: SFML Compiler Setup & Portable Builds
* **The Problem**: SFML is a third-party library. Standard GCC compilers do not include `<SFML/Graphics.hpp>`. Copy-pasting SFML headers into `C:\MinGW\include\` often corrupts the compiler or causes 32-bit/64-bit architecture mismatches.
* **Our Solution**:
  Created **`03-cpp-sfml-graphics/`** with a portable local structure and an automated 1-click `build.bat` script:
  - Place your downloaded GCC MinGW `SFML/` folder directly inside `03-cpp-sfml-graphics/` (`SFML/include`, `SFML/lib`, `SFML/bin`).
  - Running `.\build.bat` automatically passes compiler flags (`-I SFML/include -L SFML/lib`) and outputs compiled binaries cleanly into `bin/`.

---

### Challenge 4: Desktop GUI Window without Third-Party Libraries
* **The Problem**: Wanting a real graphical GUI desktop window without installing external libraries like SFML or modifying compiler files.
* **Our Solution**:
  Created **`02-cpp-win32-gui/`**.
  - Uses native Windows GDI graphics (`<windows.h>` + `g++ main.cpp -o bin/hanoi-win32-gui.exe -lgdi32 -mwindows`).
  - Employs double-buffered bitmap rendering (`BitBlt`) to draw flicker-free colorful disks and animated moves.
  - **Zero external downloads required!** Runs out-of-the-box on any Windows machine.

---

### Challenge 5: C++ Toolchain ABI & Compiler Mismatches (GCC vs MSVC)
* **The Problem**: Trying to link MSVC-built SFML `.lib` files using MinGW GCC `g++` throws `undefined reference to __imp__...` errors.
* **Why this happens (Engineering Principle)**:
  Unlike C or Java, C++ lacks a standardized Application Binary Interface (ABI) across compilers. GCC (`g++`) and Microsoft Visual C++ (`cl.exe`) use completely different function name mangling schemes, class memory layouts, and standard library implementations (`libstdc++` vs `MSVC STL`).
* **Our Solution**:
  - Educate team: Always download **MinGW GCC version** of SFML when compiling with MinGW `g++`.
  - Alternatively use native GDI (`02-cpp-win32-gui`) which uses standard C Win32 API handles compatible with all C++ compilers.

---

### Challenge 6: Build Artifact Isolation & Directory Hygiene
* **The Problem**: Outputting `.exe` binaries into source directories creates clutter and ambiguity about which source file produced which executable.
* **Our Solution**:
  Implemented professional **Build Isolation**:
  - Every module compiles its executable into a dedicated `bin/` directory (e.g. `01-cpp-iostream/bin/hanoi-iostream.exe`).
  - Source directories contain ONLY source files (`main.cpp`) and documentation (`EXPLANATION.md`).
  - `.gitignore` ignores `**/bin/` to keep source control repositories clean.

---

## 📁 Professional Directory Layout Overview

| Folder Name | Language & API | Compiled Binary Output Path | Best For |
| :--- | :--- | :--- | :--- |
| **`01-cpp-iostream/`** | C++ (`<iostream>` ONLY) | `01-cpp-iostream/bin/hanoi-iostream.exe` | Strict teachers forbidding extra libraries |
| **`02-cpp-win32-gui/`** | C++ (Win32 GDI) | `02-cpp-win32-gui/bin/hanoi-win32-gui.exe` | Standalone native Windows GUI submission |
| **`03-cpp-sfml-graphics/`** | C++ (SFML 2D GUI) | `03-cpp-sfml-graphics/bin/hanoi-sfml.exe` | Rich 2D graphical visualizer using SFML |
| **`04-cpp-windows-color/`** | C++ (`<windows.h>`) | `04-cpp-windows-color/bin/hanoi-win-color.exe` | Colorful terminal visualizer |
| **`05-java-console/`** | Java (`TowerOfHanoi.java`) | `05-java-console/bin/TowerOfHanoi.class` | Java coursework requirements |

---

## 💻 Quick Reference Commands

```powershell
# 1. Pure iostream C++
cd 01-cpp-iostream
g++ main.cpp -o bin/hanoi-iostream.exe
.\bin\hanoi-iostream.exe

# 2. Native Windows GUI (Zero setup needed!)
cd ..\02-cpp-win32-gui
g++ main.cpp -o bin/hanoi-win32-gui.exe -lgdi32 -mwindows
.\bin\hanoi-win32-gui.exe

# 3. SFML 2D Animation (Automated Build Script)
cd ..\03-cpp-sfml_graphics
.\build.bat

# 4. Windows Colored Console
cd ..\04-cpp-windows-color
g++ main.cpp -o bin/hanoi-win-color.exe
.\bin\hanoi-win-color.exe

# 5. Java Version
cd ..\05-java-console
javac -d bin TowerOfHanoi.java
java -cp bin TowerOfHanoi
```
