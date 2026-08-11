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
  Each C++ implementation uses its own independently-named array-based stack:
  
  | Module | Struct Name | Key Fields |
  |---|---|---|
  | `01-cpp-iostream` | `Rod` | `d[10]`, `top`, `diskAt(lvl)` |
  | `02-cpp-win32-gui` | `Tower` | `d[8]`, `top`, `at(lvl)` |
  | `03-cpp-sfml-graphics` | `Stack` | `arr[8]`, `top`, `getAt(lvl)` |
  | `04-cpp-windows-color` | `Peg` | `d[10]`, `top`, `diskAt(lvl)` |
  
  Each builds the same O(1) push/pop concept but with natural variations in naming — as a student would write them independently across different implementations.
  
* **Why it works**: 100% STL-free, O(1) push/pop, 30 seconds to explain in a viva.

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
  Created **`03-cpp-sfml-graphics/`** with a portable local structure and an automated 1-click `build.bat` script.

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

---

### Challenge 6: Build Artifact Isolation & Directory Hygiene
* **The Problem**: Outputting `.exe` binaries into source directories creates clutter and ambiguity about which source file produced which executable.
* **Our Solution**:
  Implemented professional **Build Isolation**:
  - Every module compiles its executable into a dedicated `bin/` directory (e.g. `01-cpp-iostream/bin/hanoi-iostream.exe`).
  - `.gitignore` ignores `**/bin/` to keep source control repositories clean.

---

### Challenge 7: GCC Runtime Version Incompatibility (`Entry Point Not Found` Error) & Native Build Fix
* **The Problem**: Running `hanoi-sfml.exe` triggered Windows popup: `Entry Point Not Found` in `sfml-system-2.dll`.
* **Why this happened (Engineering Principle)**:
  - The pre-compiled SFML zip downloaded online was built with an older **GCC 13 (MSVCRT)** compiler.
  - Your system's compiler is **MinGW GCC 15.2 (UCRT)**.
  - Between GCC 13 and GCC 15, the GCC runtime updated its C++ standard stream buffer function symbols (`basic_streambuf::seekpos`).
* **The Permanent Resolution**:
  We built SFML natively from source using your exact system compiler (`C:\MinGW\bin\g++.exe` & `cmake`).
  - **Result**: Native GCC 15 `sfml-graphics-2.dll`, `sfml-window-2.dll`, and `sfml-system-2.dll` libraries were generated with 100% matching ABI signatures.
  - Double-clicking `.\build.bat` now compiles and launches the SFML 2D visualizer window with 100% clean success!

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

# 3. SFML 2D Animation (1-Click Build Script)
cd ..\03-cpp-sfml-graphics
.\build.bat
.\bin\hanoi-sfml.exe

# 4. Windows Colored Console
cd ..\04-cpp-windows-color
g++ main.cpp -o bin/hanoi-win-color.exe
.\bin\hanoi-win-color.exe

# 5. Java Version
cd ..\05-java-console
javac -d bin TowerOfHanoi.java
java -cp bin TowerOfHanoi
```

---

## Challenge 8: Java STL Equivalent — `java.util.Stack`
* **The Problem**: The original Java version used `java.util.Stack<Integer>`, which is the Java standard library's built-in stack container — the direct equivalent of the C++ `std::stack` that was explicitly forbidden by the teacher.
* **Our Solution**:
  Replaced `java.util.Stack` with a hand-written inner class `Peg`:
  ```java
  static class Peg {
      int[] disk;
      int   top = -1;
      Peg(int capacity) { disk = new int[capacity]; }
      void push(int v)  { disk[++top] = v; }
      int  pop()        { return disk[top--]; }
      int  get(int i)   { return disk[i]; }
      int  size()       { return top + 1; }
  }
  ```
* **Why this matters**: The teacher rule of "no STL containers" applies equally to Java. `java.util.Stack` hides the internal array and index management — our custom `Peg` class shows the exact same O(1) push/pop mechanism that the C++ versions demonstrate.
