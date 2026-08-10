# Tower of Hanoi - Professional Project Workspace

This repository contains all implementations of the **Tower of Hanoi** problem organized according to professional software engineering standards (kebab-case directory naming, isolated `bin/` build outputs, and zero-pollution source trees).

> 📘 **Detailed Technical Guide**: Read [CHALLENGES_AND_SOLUTIONS.md](file:///c:/Users/Dell/Desktop/proj/CHALLENGES_AND_SOLUTIONS.md) for a full breakdown of compiler ABI mangling (GCC vs MSVC), custom stack algorithms, viva defense notes, and directory hygiene.

---

## 📁 Directory Structure & Implementations

```text
proj/
├── 01-cpp-iostream/        # Pure standard C++ (#include <iostream> ONLY, zero extra headers)
├── 02-cpp-win32-gui/        # Native Windows Desktop GUI Window (-lgdi32, zero 3rd-party downloads)
├── 03-cpp-sfml-graphics/    # SFML 2D GUI Window Animation + 1-click build.bat
├── 04-cpp-windows-color/    # Console colorful visualizer (<windows.h> + Sleep)
├── 05-java-console/         # Pure Java implementation (TowerOfHanoi.java)
├── CHALLENGES_AND_SOLUTIONS.md  # Complete technical challenge & ABI guide
└── README.md                # Project hub overview
```

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
# Paste your downloaded GCC MinGW SFML folder inside 03-cpp-sfml-graphics/
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
