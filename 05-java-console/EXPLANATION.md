# 05-java-console

Java console visualizer. Uses a hand-written inner class for the stack instead of `java.util.Stack`.

## Build
```powershell
javac -d bin TowerOfHanoi.java
java -cp bin TowerOfHanoi
```

## Design

**`class Peg`** — inner static class implementing an array-based stack:
```java
static class Peg {
    int[] disk;
    int   top = -1;

    Peg(int capacity) { disk = new int[capacity]; }
    void push(int v)  { disk[++top] = v; }
    int  pop()        { return disk[top--]; }
    int  get(int i)   { return disk[i]; }
    int  size()       { return top + 1; }
}
```

**`move(k, from, to, helper, ...)`** — recursive solver. At `k == 1`, it directly moves the disk, prints the step, and calls `show()`. For larger `k`, it follows the standard three-step recursion.

**`show()`** — prints the current state of all three rods. Loops from the highest level down, calling `printLevel` for each rod at each height.

**`printLevel(rod, lvl)`** — prints a single row for one rod. If a disk exists at that level it prints its width as `*` characters (wider for larger disks); otherwise it prints a `|` centered in the same space.

## Notes

- `static class Peg` is a nested class: declared inside `TowerOfHanoi` but accessible to all `static` methods without an outer class instance.
- `sc.close()` releases the `Scanner` and its underlying input stream at the end of execution.
- Time complexity: **O(2ⁿ)** — 7 moves for 3 disks, 255 moves for 8 disks.
