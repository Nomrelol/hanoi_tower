# Tower of Hanoi - Single Header (`<iostream>`) Teacher Guide

This guide explains the simplified C++ implementation in [main.cpp](file:///c:/Users/Dell/Desktop/proj/01_cpp_iostream_only/main.cpp).

> [!NOTE]
> **Key Feature**: The code uses **ONLY `#include <iostream>`**.
> - No `<windows.h>`, `<vector>`, `<stack>`, `<cstdlib>`, `<thread>`, or `<chrono>`.
> - 100% pure standard C++ features that are super easy to explain in a teacher viva.

---

## Line-by-Line Code Breakdown

### 1. Custom Stack (`struct Stack`)
```cpp
struct Stack {
    int arr[10];   // Holds disk sizes (1 to 8)
    int top = -1;  // Index of the top disk (-1 when empty)

    void push(int disk) { arr[++top] = disk; }
    int pop() { return (top == -1) ? 0 : arr[top--]; }
    int peek() { return (top == -1) ? 0 : arr[top]; }
    bool isEmpty() { return top == -1; }
    int getAt(int level) { return (level <= top) ? arr[level] : 0; }
};
```
* **`arr[10]`**: Fixed array storing disk diameters.
* **`top = -1`**: Track top element index. `push()` increments `top`, `pop()` decrements `top`.
* **`getAt(level)`**: Allows drawing the tower level by level without modifying the stack.

---

### 2. Pure `<iostream>` Delay Loop (`delay`)
```cpp
void delay() {
    for (volatile long long i = 0; i < 150000000; i++) {
        // Simple empty loop to create delay between frames
    }
}
```
* **Teacher Explanation**: *"Instead of using external headers like `<windows.h>` or `<thread>`, we use a simple loop `delay()` that executes 150 million iterations to pause execution for roughly half a second between steps."*

---

### 3. Screen Clearing & Display (`draw`)
```cpp
void draw(int disk = 0, char from = ' ', char to = ' ') {
    for (int i = 0; i < 30; i++) cout << "\n";
    ...
```
* **Teacher Explanation**: *"To clear the console screen using pure `<iostream>`, we print 30 newlines. Then we loop from the top height level down to level 0. For each rod, if a disk exists at that level (`d > 0`), we print `[= d =]`. Otherwise, we print the rod axis `|`."*

---

### 4. Recursive Solution (`solve`)
```cpp
void solve(int n, Stack &src, Stack &aux, Stack &dest, char s, char a, char d) {
    if (n == 1) {
        moveDisk(src, dest, s, d);
        return;
    }
    solve(n - 1, src, dest, aux, s, d, a);
    moveDisk(src, dest, s, d);
    solve(n - 1, aux, src, dest, a, s, d);
}
```
* **Base case (`n == 1`)**: Move single disk directly from source rod to destination rod.
* **Recursive step**:
  1. Move `n - 1` disks from `src` to `aux`.
  2. Move bottom disk from `src` to `dest`.
  3. Move `n - 1` disks from `aux` to `dest`.
