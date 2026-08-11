# Implementation Notes

Technical notes covering design decisions, build setup, and known toolchain issues across all five modules.

---

## Custom Stack Implementation

All five modules implement their own array-based stack rather than using standard container libraries. The pattern is the same in every case:

```cpp
struct Rod {
    int  d[MAX];
    int  top = -1;

    void push(int v)    { d[++top] = v; }
    int  pop()          { return d[top--]; }
    bool isEmpty()      { return top == -1; }
    int  diskAt(int i)  { return (i <= top) ? d[i] : 0; }
};
```

- `push` / `pop` run in O(1)
- `diskAt(level)` is used by the drawing functions to read any position in the stack, not just the top
- Each module names its struct differently (`Rod`, `Tower`, `Stack`, `Peg`) since they were written as separate, independent implementations

---

## Build Isolation

Every module outputs its compiled binary into its own `bin/` subdirectory:

| Module | Output |
|---|---|
| `01-cpp-iostream` | `bin/hanoi-iostream.exe` |
| `02-cpp-win32-gui` | `bin/hanoi-win32-gui.exe` |
| `03-cpp-sfml-graphics` | `bin/hanoi-sfml.exe` |
| `04-cpp-windows-color` | `bin/hanoi-win-color.exe` |
| `05-java-console` | `bin/TowerOfHanoi.class` |

The `bin/` directories are listed in `.gitignore` and are not committed to version control.

---

## SFML — Portable Local Build

SFML is kept inside `03-cpp-sfml-graphics/SFML/` rather than installed globally. The `build.bat` script passes the correct `-I` and `-L` paths to the compiler and copies the required DLLs to `bin/` automatically.

**Why local instead of global?** Installing SFML headers into `C:\MinGW\include\` risks overwriting other headers and introduces 32/64-bit architecture conflicts if the wrong build is used.

---

## C++ ABI Mismatch (GCC vs MSVC)

Linking MSVC-compiled SFML `.lib` files with MinGW `g++` produces linker errors like:

```
undefined reference to `__imp__ZN2sf5ColorC1Ehhhh'
```

This happens because GCC and MSVC use different C++ Application Binary Interfaces — different name mangling, different class layouts, different runtime libraries (`libstdc++` vs MSVC STL). The solution is to use SFML binaries built specifically for the same GCC version in use.

---

## GCC Runtime Version Mismatch

If `hanoi-sfml.exe` shows a Windows popup `Entry Point Not Found` in `sfml-system-2.dll`, the SFML DLLs were built with a different GCC version than the compiler being used.

- Pre-built SFML zips online often target GCC 13 (MSVCRT runtime)
- MinGW GCC 15 uses the UCRT runtime with updated symbol names (e.g., `basic_streambuf::seekpos`)

Fix: use SFML binaries built for the same GCC version as your system compiler.

---

## Win32 GUI — Window Safety

The Win32 module uses a global `g_hwnd` and calls `IsWindow(g_hwnd)` before every draw operation inside the animation loop. This prevents a crash if the user closes the window while the recursive solver is still running.

---

## Java — No java.util.Stack

The Java module uses a hand-written inner class `Peg` instead of `java.util.Stack`. The structure is identical in concept to the C++ implementations — an `int[]` array with a `top` index, and manual push/pop methods.
