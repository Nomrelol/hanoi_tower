#include <iostream>
#include <windows.h> // For Sleep(), system("cls"), and console colors

using namespace std;

const int MAX_DISKS = 10;

// Custom Stack structure (No STL container used)
struct RodStack {
    int disks[MAX_DISKS];
    int top;

    RodStack() { top = -1; }

    void push(int diskSize) {
        if (top < MAX_DISKS - 1) disks[++top] = diskSize;
    }

    int pop() {
        if (top == -1) return 0;
        return disks[top--];
    }

    int peek() {
        if (top == -1) return 0;
        return disks[top];
    }

    bool isEmpty() { return top == -1; }

    int getDiskAt(int level) {
        if (level >= 0 && level <= top) return disks[level];
        return 0;
    }
};

RodStack rodA, rodB, rodC;
int totalDisks = 3;
int stepCounter = 0;
int animationDelayMs = 500;

void setColor(int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

void printChar(char ch, int count) {
    for (int i = 0; i < count; i++) cout << ch;
}

void drawRods(int movedDisk = 0, char fromRod = ' ', char toRod = ' ') {
    system("cls");

    setColor(14);
    cout << "========================================================\n";
    cout << "           TOWER OF HANOI (WINDOWS COLORFUL)            \n";
    cout << "========================================================\n\n";

    setColor(15);
    if (stepCounter == 0) {
        cout << " Initial State: All " << totalDisks << " disks stacked on Rod A\n\n";
    } else {
        cout << " Step " << stepCounter << ": Moved Disk [" << movedDisk 
             << "] from Rod " << fromRod << " to Rod " << toRod << "\n\n";
    }

    int maxFieldWidth = (totalDisks * 2) + 3;

    for (int level = totalDisks - 1; level >= 0; level--) {
        // Rod A
        int sizeA = rodA.getDiskAt(level);
        int spacesA = (maxFieldWidth - (sizeA * 2 + 1)) / 2;
        printChar(' ', spacesA);
        if (sizeA > 0) {
            setColor(9 + (sizeA % 6));
            cout << "<"; printChar('=', sizeA - 1); cout << sizeA; printChar('=', sizeA - 1); cout << ">";
        } else {
            setColor(8); cout << "|";
        }
        setColor(15); printChar(' ', spacesA + 4);

        // Rod B
        int sizeB = rodB.getDiskAt(level);
        int spacesB = (maxFieldWidth - (sizeB * 2 + 1)) / 2;
        printChar(' ', spacesB);
        if (sizeB > 0) {
            setColor(9 + (sizeB % 6));
            cout << "<"; printChar('=', sizeB - 1); cout << sizeB; printChar('=', sizeB - 1); cout << ">";
        } else {
            setColor(8); cout << "|";
        }
        setColor(15); printChar(' ', spacesB + 4);

        // Rod C
        int sizeC = rodC.getDiskAt(level);
        int spacesC = (maxFieldWidth - (sizeC * 2 + 1)) / 2;
        printChar(' ', spacesC);
        if (sizeC > 0) {
            setColor(9 + (sizeC % 6));
            cout << "<"; printChar('=', sizeC - 1); cout << sizeC; printChar('=', sizeC - 1); cout << ">";
        } else {
            setColor(8); cout << "|";
        }
        setColor(15); cout << "\n";
    }

    setColor(7);
    int baseWidth = maxFieldWidth;
    printChar('=', baseWidth); cout << "    ";
    printChar('=', baseWidth); cout << "    ";
    printChar('=', baseWidth); cout << "\n";

    int padding = baseWidth / 2;
    setColor(11);
    printChar(' ', padding); cout << "ROD A"; printChar(' ', padding + 4);
    printChar(' ', padding); cout << "ROD B"; printChar(' ', padding + 4);
    printChar(' ', padding); cout << "ROD C"; cout << "\n\n";

    setColor(15);
    Sleep(animationDelayMs);
}

void moveDisk(RodStack &source, RodStack &dest, char fromRod, char toRod) {
    int disk = source.pop();
    dest.push(disk);
    stepCounter++;
    drawRods(disk, fromRod, toRod);
}

void solveHanoi(int n, RodStack &source, RodStack &aux, RodStack &dest,
                char sourceName, char auxName, char destName) {
    if (n == 1) {
        moveDisk(source, dest, sourceName, destName);
        return;
    }
    solveHanoi(n - 1, source, dest, aux, sourceName, destName, auxName);
    moveDisk(source, dest, sourceName, destName);
    solveHanoi(n - 1, aux, source, dest, auxName, sourceName, destName);
}

int main() {
    setColor(14);
    cout << "Enter number of disks (1 to 8): ";
    setColor(15);
    cin >> totalDisks;
    if (totalDisks < 1 || totalDisks > 8) totalDisks = 3;

    for (int i = totalDisks; i >= 1; i--) rodA.push(i);

    drawRods();

    setColor(10);
    cout << "\nPress ENTER to start solution...";
    cin.ignore();
    cin.get();

    solveHanoi(totalDisks, rodA, rodB, rodC, 'A', 'B', 'C');

    setColor(10);
    cout << "\nSOLVED SUCCESSFULLY IN " << stepCounter << " MOVES!\n\n";
    setColor(15);
    return 0;
}
