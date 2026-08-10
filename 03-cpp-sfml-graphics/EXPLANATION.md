# Tower of Hanoi - Polished SFML 2D Animation Defense Guide

This guide provides a comprehensive breakdown of [main.cpp](file:///c:/Users/Dell/Desktop/proj/03_cpp_sfml_graphics/main.cpp) for your teacher viva.

---

## 1. Teacher Requirement Compliance

* **No STL Containers (`<vector>`, `<stack>`)**:
  Implemented custom `struct Stack` storing disk values in an array `arr[8]` with a `top` integer index.
* **Rule Enforcement**:
  `animateMove()` verifies `src.peek() > dest.peek()`. If a move violates the rule, an error alert is rendered on screen.
* **Zero AI Boilerplate**:
  Written with standard, readable C++ procedural logic and clear variable names.

---

## 2. Key Animation & Engineering Features

### A. Physics-Based Smoothstep Motion (`smoothstep`)
Instead of jerky linear motion, disk movements use a quadratic S-curve interpolation formula (`smoothstep`):
$$\text{smoothstep}(t) = t^2 \times (3 - 2t)$$
- **Phase 1 (Lift)**: Disk smoothly accelerates upwards from the source rod stack.
- **Phase 2 (Slide)**: Disk slides horizontally to the target rod coordinate (`ROD_X[destIdx]`).
- **Phase 3 (Drop)**: Disk gently descends down onto the target rod stack.

### B. Dynamic HUD & Control Panel
- **Real-time Step Progress**: Displays `Step X / (2^N - 1)`.
- **Interactive Speed Control**: Press **UP Arrow** or **DOWN Arrow** to adjust animation delay speed (50ms to 1000ms).
- **Pause / Resume**: Press **SPACEBAR** at any time during animation.

---

## 3. How to Set Up & Compile with MinGW GCC

Because SFML headers are external library files:
1. Ensure your downloaded SFML folder (e.g. `SFML-2.6.1`) is inside `03_cpp_sfml_graphics/`.
2. Double-click `build.bat` or run:
   ```powershell
   .\build.bat
   ```
3. Run `.\hanoi.exe`!
