# 03-cpp-sfml-graphics — SFML 2D Animated Visualizer

**File**: [main.cpp](file:///c:/Users/Dell/Desktop/proj/03-cpp-sfml-graphics/main.cpp)

> [!NOTE]
> Requires the SFML GCC MinGW build already placed in `03-cpp-sfml-graphics/SFML/`.  
> Run `build.bat` — it compiles and copies the needed DLLs automatically.

---

## Compile & Run
```powershell
cd 03-cpp-sfml-graphics
.\build.bat
.\bin\hanoi-sfml.exe
```
*Console asks for disk count first, then the animated window opens.*

---

## What the code does

1. **`struct Stack`** — custom array stack (same idea as `Rod`/`Tower`/`Peg` in other versions, independently written for SFML context).

2. **`renderScene(window, font)`** — draws background, base platform, three rods, all disks as coloured rectangles using `sf::RectangleShape`, plus HUD text.

3. **`animateMove(...)`** — three-phase smooth animation per disk move:
   - Phase 1: Lift disk straight up
   - Phase 2: Slide horizontally to target rod
   - Phase 3: Drop disk down onto stack
   Each phase uses a `smoothstep` easing curve for realistic motion.

4. **`solveHanoiSFML(window, n, ...)`** — recursive solver that calls `animateMove` instead of an instant move.

5. **Keyboard controls** (while window is open):
   - `1`–`8` → change disk count and reset
   - `SPACE` / `ENTER` → start solving
   - `↑` / `↓` → adjust animation speed
   - `R` → reset puzzle

---

## Runtime Controls
| Key | Action |
|---|---|
| `1`–`8` | Select number of disks |
| `SPACE` or `ENTER` | Start solving |
| `↑` | Speed up (−50ms) |
| `↓` | Slow down (+50ms) |
| `R` | Reset puzzle |

---

## Teacher Viva Q&A

| Question | Answer |
|---|---|
| What is SFML? | Simple and Fast Multimedia Library — a C++ library for 2D graphics |
| Why `smoothstep`? | Gives ease-in/ease-out motion instead of robotic constant speed |
| What does `setOrigin` do? | Sets the reference point of the shape so it centres properly on the rod |
| Why a `build.bat`? | SFML needs `-I` include path and `-L` lib path — the script handles it automatically |
| Why GCC MinGW SFML specifically? | SFML `.a` libs must match the compiler ABI; MSVC `.lib` files don't work with `g++` |
