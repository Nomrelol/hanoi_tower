# Tower of Hanoi - Technical Challenges, Solutions & Branch Architecture Guide

This comprehensive guide documents all the technical challenges faced, teacher constraints enforced, design decisions made, and branch implementations created during the development of this project.

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
  Created the **`cpp-iostream-only`** branch.
  - Contains **ONLY `#include <iostream>`** — zero external headers.
  - Screen refresh handled via `cout` newlines.
  - Delay timing handled via a simple `for` spin loop.
  - Accompanied by a detailed `EXPLANATION.md` viva cheat sheet.

---

### Challenge 3: SFML Compiler Errors (`SFML/Graphics.hpp: No such file or directory`)
* **The Problem**: SFML is a third-party library. Standard GCC compilers do not include `<SFML/Graphics.hpp>`. Copy-pasting SFML headers into `C:\MinGW\include\` often corrupts the compiler or causes 32-bit/64-bit architecture mismatches.
* **Our Solution**:
  Created the **`cpp-sfml-graphics`** branch with a portable local structure and an automated 1-click `build.bat` script:
  - Place `SFML/` folder directly inside the project workspace (`SFML/include`, `SFML/lib`, `SFML/bin`).
  - Running `.\build.bat` automatically passes compiler flags (`-I SFML/include -L SFML/lib`) and copies runtime `.dll` files automatically.

---

### Challenge 4: Desktop GUI Window without Third-Party Libraries
* **The Problem**: Wanting a real graphical GUI desktop window without installing external libraries like SFML or modifying compiler files.
* **Our Solution**:
  Created the **`cpp-win32-gui`** branch.
  - Uses native Windows GDI graphics (`<windows.h>` + `g++ main.cpp -o hanoi_gui.exe -lgdi32 -mwindows`).
  - Employs double-buffered bitmap rendering (`BitBlt`) to draw flicker-free colorful disks and animated moves.
  - **Zero external downloads required!** Runs out-of-the-box on any Windows machine.

---

## 🔀 Branch Architecture Overview

| Branch Name | Language & API | Main Features | Best For | How to Switch |
| :--- | :--- | :--- | :--- | :--- |
| **`cpp-iostream-only`** | C++ (`<iostream>` ONLY) | **Zero extra headers**, pure standard C++, custom stack | Strict teachers forbidding extra libraries | `git checkout cpp-iostream-only` |
| **`cpp-win32-gui`** | C++ (Win32 GDI) | **Native Desktop GUI window**, zero third-party downloads | Standalone Windows GUI submission | `git checkout cpp-win32-gui` |
| **`cpp-sfml-graphics`** | C++ (SFML 2D GUI) | Smooth 2D disk animation window, 1-click `build.bat` | Rich 2D graphical visualizer using SFML | `git checkout cpp-sfml-graphics` |
| **`cpp-windows-color`** | C++ (`<windows.h>`) | Console disk blocks with Windows colors & `Sleep()` | Colorful terminal presentation | `git checkout cpp-windows-color` |
| **`java-version`** | Java (`TowerOfHanoi.java`) | Star (`*`) block graphic disk rendering | Java coursework requirements | `git checkout java-version` |

---

## 💻 Quick Reference Commands

```powershell
# Switch to Pure iostream C++
git checkout cpp-iostream-only
g++ main.cpp -o hanoi.exe
.\hanoi.exe

# Switch to Native Windows GUI (Zero setup needed!)
git checkout cpp-win32-gui
g++ main.cpp -o hanoi_gui.exe -lgdi32 -mwindows
.\hanoi_gui.exe

# Switch to SFML 2D Animation (Automated Build Script)
git checkout cpp-sfml-graphics
.\build.bat

# Switch to Java Version
git checkout java-version
javac TowerOfHanoi.java
java TowerOfHanoi
```
