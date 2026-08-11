# 05-java-console — Pure Java Console Visualizer

**File**: [TowerOfHanoi.java](file:///c:/Users/Dell/Desktop/proj/05-java-console/TowerOfHanoi.java)

> [!NOTE]
> **No `java.util.Stack` used.** A hand-written inner class `Peg` replaces it (array + `top` index).  
> Only `import java.util.Scanner` — for reading user input.

---

## Compile & Run
```powershell
cd 05-java-console
javac -d bin TowerOfHanoi.java
java -cp bin TowerOfHanoi
```

---

## What the code does

1. **Inner class `Peg`** — custom stack:
   ```java
   static class Peg {
       int[] disk;
       int   top = -1;
       Peg(int capacity) { disk = new int[capacity]; }
       void push(int v)  { disk[++top] = v; }
       int  pop()        { return disk[top--]; }
   }
   ```
   This mirrors the C++ `struct Rod / Tower / Peg` in the other implementations.

2. **`move(k, from, to, helper, ...)`** — recursive solver:
   - Base case: move directly and print the step.
   - Recursive: move n−1 to helper, move largest, move n−1 from helper to destination.

3. **`show()`** — loops from top level down, printing each rod's disk state using `*` characters.

4. **Move counter** — `moves++` is tracked and printed at the end.

---

## Teacher Viva Q&A

| Question | Answer |
|---|---|
| Why `static class Peg`? | It's a nested class — defined inside `TowerOfHanoi` but shared across all `static` methods |
| Why not `java.util.Stack`? | The teacher rule prohibits STL containers — Java's `Stack` is the direct equivalent |
| What does `sc.close()` do? | Properly releases the `Scanner` resource at the end |
| What is the time complexity? | O(2ⁿ) moves — for 8 disks that is 255 total moves |
