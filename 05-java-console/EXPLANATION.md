# Tower of Hanoi - Java Console Defense Guide

This guide explains the Java implementation in [TowerOfHanoi.java](file:///c:/Users/Dell/Desktop/proj/05-java-console/TowerOfHanoi.java).

> [!NOTE]
> **Key Feature**:
> - Standard OOP Java structure.
> - Star (`*`) block graphic disk rendering frame by frame.

---

## How to Compile & Run
```powershell
javac -d bin TowerOfHanoi.java
java -cp bin TowerOfHanoi
```

---

## Code Breakdown for Oral Defense
- **`move(disk, from, to, helper, start, end, extra)`**: Standard 3-step recursive function.
- **`show()`**: Renders disks level by level from height `total` down to `1`.
- **`printRod(rod, level)`**: Calculates required spacing and draws `*` blocks proportional to disk size.
