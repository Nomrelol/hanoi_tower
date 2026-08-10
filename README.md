# Tower of Hanoi - Complete Project Workspace

This repository contains all implementations of the **Tower of Hanoi** problem organized cleanly into subdirectories so you can explore, edit, and compare them simultaneously in your code editor.

> 📘 **Detailed Technical Guide**: Read [CHALLENGES_AND_SOLUTIONS.md](file:///c:/Users/Dell/Desktop/proj/CHALLENGES_AND_SOLUTIONS.md) for a full breakdown of teacher constraints, custom stack algorithms, viva defense notes, and compiler setups.

---

## 📁 Directory Structure & Implementations

```text
proj/
├── 01_cpp_iostream_only/   # Pure standard C++ (#include <iostream> ONLY, zero extra headers)
├── 02_cpp_win32_gui/       # Native Windows Desktop GUI Window (-lgdi32, zero 3rd-party downloads)
├── 03_cpp_sfml_graphics/   # SFML 2D GUI Window Animation + 1-click build.bat
├── 04_cpp_windows_color/   # Console colorful visualizer (<windows.h> + Sleep)
├── 05_java_version/        # Pure Java implementation (TowerOfHanoi.java)
├── CHALLENGES_AND_SOLUTIONS.md  # Complete technical challenge & solution guide
└── README.md               # Project hub overview
```

---

## 🚀 How to Run Each Implementation

### 1. Pure C++ (`iostream` ONLY)
```powershell
cd 01_cpp_iostream_only
g++ main.cpp -o hanoi.exe
.\hanoi.exe
```

### 2. Native Windows Desktop GUI Window (Zero Setup!)
```powershell
cd 02_cpp_win32_gui
g++ main.cpp -o hanoi_gui.exe -lgdi32 -mwindows
.\hanoi_gui.exe
```

### 3. SFML 2D Graphical Animation
```powershell
cd 03_cpp_sfml_graphics
# Paste your downloaded SFML folder inside 03_cpp_sfml_graphics/
.\build.bat
.\hanoi.exe
```

### 4. Windows Colored Console
```powershell
cd 04_cpp_windows_color
g++ main.cpp -o hanoi.exe
.\hanoi.exe
```

### 5. Java Version
```powershell
cd 05_java_version
javac TowerOfHanoi.java
java TowerOfHanoi
```
