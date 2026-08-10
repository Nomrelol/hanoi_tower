# Tower of Hanoi - Project Version Hub

This repository contains multiple implementations of the **Tower of Hanoi** problem, organized into Git branches so you can easily switch based on your teacher's requirements.

> 📘 **Detailed Technical Guide**: Read [CHALLENGES_AND_SOLUTIONS.md](file:///c:/Users/Dell/Desktop/proj/CHALLENGES_AND_SOLUTIONS.md) for a full breakdown of all teacher constraints, compiler issues, design decisions, and solutions across all branches.

---

## 🔀 Available Versions & How to Switch

You can switch between any version anytime using the command `git checkout <branch-name>`:

| Branch Name | Language | Main Features | Teacher / Use Case |
| :--- | :--- | :--- | :--- |
| **`cpp-iostream-only`** | C++ | **ONLY `#include <iostream>`**<br>- No extra libraries/headers<br>- Custom `Stack` (No STL)<br>- Pure C++ delay loop & screen refresh | **Best for strict teachers** who forbid external libraries/headers. |
| **`cpp-win32-gui`** | C++ | **Native Windows Desktop GUI Window**<br>- Zero 3rd-party downloads needed!<br>- Double-buffered smooth graphics (`-lgdi32`) | Best for native desktop GUI window presentation without downloading SFML. |
| **`cpp-sfml-graphics`** | C++ | **SFML 2D GUI Window Animation**<br>- 2D graphical window with smooth 3-phase disk sliding<br>- Color palette & live HUD text<br>- 1-click `build.bat` script | Best for rich graphical demonstration using SFML. |
| **`cpp-windows-color`** | C++ | **`<windows.h>` + Console Colors**<br>- Vibrant color-coded disks<br>- Accurate `Sleep()` delays<br>- Custom `Stack` (No STL) | Best for colored terminal visual presentations. |
| **`java-version`** | Java | **Pure Java (`TowerOfHanoi.java`)**<br>- Star (`*`) block graphic disk rendering<br>- Clean OOP recursion | Best if your teacher requests a Java submission. |

---

## 💻 Quick Switching Commands

```bash
# Pure C++ (iostream ONLY)
git checkout cpp-iostream-only

# Native Windows Desktop GUI Window (Zero Downloads)
git checkout cpp-win32-gui

# SFML 2D Graphical Animation
git checkout cpp-sfml-graphics

# Windows Colored Terminal
git checkout cpp-windows-color

# Java Version
git checkout java-version
```

---

## 📖 Defense Cheat Sheet
Each branch includes a tailored `EXPLANATION.md` file explaining the code line-by-line for viva/oral exams.
