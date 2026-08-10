# Tower of Hanoi - Project Version Hub

This repository contains multiple implementations of the **Tower of Hanoi** problem, organized into Git branches so you can easily switch based on your teacher's requirements.

---

## 🔀 Available Versions & How to Switch

You can switch between any version anytime using the command `git checkout <branch-name>`:

| Branch Name | Language | Main Features | Teacher / Use Case |
| :--- | :--- | :--- | :--- |
| **`cpp-iostream-only`** | C++ | **ONLY `#include <iostream>`**<br>- No `<windows.h>` or `<cstdlib>`<br>- Custom `Stack` (No STL)<br>- Pure C++ delay loop & screen refresh | **Best for strict teachers** who forbid external libraries/headers. |
| **`cpp-windows-color`** | C++ | **`<windows.h>` + Console Colors**<br>- Vibrant color-coded disks<br>- Accurate `Sleep()` delays<br>- Custom `Stack` (No STL) | Best for visual demonstrations and presentations. |
| **`java-version`** | Java | **Pure Java (`TowerOfHanoi.java`)**<br>- Star (`*`) block graphic disk rendering<br>- Clean OOP recursion | Best if your teacher requests a Java submission. |

---

## 💻 Quick Switching Commands

To switch to **C++ Pure `iostream` (No Extra Libraries)**:
```bash
git checkout cpp-iostream-only
```

To switch to **C++ Windows Colored Version**:
```bash
git checkout cpp-windows-color
```

To switch to **Java Version**:
```bash
git checkout java-version
```

---

## 📖 Defense Cheat Sheet
Each branch includes a tailored `EXPLANATION.md` file explaining the code line-by-line for viva/oral exams.
