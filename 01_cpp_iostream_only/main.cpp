#include <iostream>

using namespace std;

const int MAX = 10;

// Custom Stack Structure (No STL library container used)
struct Stack {
    int arr[MAX];
    int top = -1;

    void push(int disk) { 
        arr[++top] = disk; 
    }
    
    int pop() { 
        if (top == -1) return 0;
        return arr[top--]; 
    }
    
    int peek() { 
        if (top == -1) return 0;
        return arr[top]; 
    }
    
    bool isEmpty() { 
        return top == -1; 
    }
    
    int getAt(int level) { 
        if (level <= top) return arr[level];
        return 0;
    }
};

Stack rodA, rodB, rodC;
int totalDisks = 3;
int moves = 0;

// Simple delay function using empty loop (no external header needed)
void delay() {
    for (volatile long long i = 0; i < 150000000; i++) {
        // Simple loop delay
    }
}

// Function to print repeated spaces
void printSpaces(int count) {
    for (int i = 0; i < count; i++) cout << " ";
}

// Function to print repeated equals signs
void printEquals(int count) {
    for (int i = 0; i < count; i++) cout << "=";
}

// Function to draw rods & disks graphically in the console
void draw(int disk = 0, char from = ' ', char to = ' ') {
    // Clear screen by printing newlines (pure iostream)
    for (int i = 0; i < 30; i++) cout << "\n";

    if (moves == 0) {
        cout << "=== TOWER OF HANOI (Initial State) ===\n\n";
    } else {
        cout << "Step " << moves << ": Moved Disk [" << disk << "] from Rod " << from << " to Rod " << to << "\n\n";
    }

    // Draw from top level down to level 0
    for (int level = totalDisks - 1; level >= 0; level--) {
        Stack* rods[3] = { &rodA, &rodB, &rodC };
        
        for (int r = 0; r < 3; r++) {
            int d = rods[r]->getAt(level);
            if (d > 0) {
                // Draw Disk
                printSpaces(totalDisks - d);
                cout << "[";
                printEquals(d);
                cout << d;
                printEquals(d);
                cout << "]";
                printSpaces(totalDisks - d);
            } else {
                // Draw empty rod line
                printSpaces(totalDisks);
                cout << " | ";
                printSpaces(totalDisks);
            }
            cout << "   ";
        }
        cout << "\n";
    }

    // Draw Bases & Labels
    int baseLen = totalDisks * 2 + 3;
    for (int i = 0; i < 3; i++) {
        printEquals(baseLen);
        cout << "   ";
    }
    cout << "\n";

    printSpaces(totalDisks); cout << "ROD A"; printSpaces(totalDisks + 2);
    printSpaces(totalDisks); cout << "ROD B"; printSpaces(totalDisks + 2);
    printSpaces(totalDisks); cout << "ROD C"; cout << "\n\n";

    delay(); // Pause execution between steps
}

// Move disk between stacks
void moveDisk(Stack &src, Stack &dest, char sName, char dName) {
    int d = src.pop();
    dest.push(d);
    moves++;
    draw(d, sName, dName);
}

// Recursive Solution
void solve(int n, Stack &src, Stack &aux, Stack &dest, char s, char a, char d) {
    if (n == 1) {
        moveDisk(src, dest, s, d);
        return;
    }
    solve(n - 1, src, dest, aux, s, d, a);
    moveDisk(src, dest, s, d);
    solve(n - 1, aux, src, dest, a, s, d);
}

int main() {
    cout << "Enter number of disks (1-8): ";
    cin >> totalDisks;
    if (totalDisks < 1 || totalDisks > 8) totalDisks = 3;

    // Load Rod A with disks
    for (int i = totalDisks; i >= 1; i--) rodA.push(i);

    draw(); // Initial display
    
    cout << "Press ENTER to start recursion...";
    cin.ignore();
    cin.get();

    solve(totalDisks, rodA, rodB, rodC, 'A', 'B', 'C');

    cout << "\n=====================================\n";
    cout << "  SOLVED SUCCESSFULLY IN " << moves << " MOVES!\n";
    cout << "=====================================\n";
    return 0;
}
