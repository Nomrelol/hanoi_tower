#include <iostream>
using namespace std;

const int MAX = 10;

// Stack implementation for disk tower
struct Rod {
    int disk[MAX];
    int top = -1;

    void push(int d)     { disk[++top] = d; }
    int  pop()           { return (top == -1) ? 0 : disk[top--]; }
    int  peek()          { return (top == -1) ? 0 : disk[top]; }
    bool isEmpty()       { return top == -1; }
    int  diskAt(int lvl) { return (lvl <= top) ? disk[lvl] : 0; }
};

Rod A, B, C;
int n;          // Number of disks
int moves = 0;
int delayLoop;  // Delay loop counter

void wait() {
    for (volatile long long i = 0; i < delayLoop; i++);
}

void printBar(int count, char ch) {
    for (int i = 0; i < count; i++) cout << ch;
}

void draw(int movedDisk = 0, char from = ' ', char to = ' ') {
    for (int i = 0; i < 35; i++) cout << '\n';

    if (moves == 0)
        cout << "  === TOWER OF HANOI | Initial State ===\n\n";
    else
        cout << "  Step " << moves << ": Disk [" << movedDisk
             << "] moved " << from << " -> " << to << "\n\n";

    for (int lvl = n - 1; lvl >= 0; lvl--) {
        Rod* rods[3] = { &A, &B, &C };
        for (int r = 0; r < 3; r++) {
            int d = rods[r]->diskAt(lvl);
            if (d > 0) {
                printBar(n - d, ' ');
                cout << '[';
                printBar(d, '=');
                cout << d;
                printBar(d, '=');
                cout << ']';
                printBar(n - d, ' ');
            } else {
                printBar(n, ' ');
                cout << " | ";
                printBar(n, ' ');
            }
            cout << "   ";
        }
        cout << '\n';
    }

    int base = n * 2 + 3;
    for (int i = 0; i < 3; i++) { printBar(base, '='); cout << "   "; }
    cout << '\n';

    printBar(n, ' '); cout << "ROD A";
    printBar(n + 2, ' ');
    printBar(n, ' '); cout << "ROD B";
    printBar(n + 2, ' ');
    printBar(n, ' '); cout << "ROD C\n\n";

    wait();
}

void move(Rod &src, Rod &dst, char s, char d) {
    int disk = src.pop();
    dst.push(disk);
    moves++;
    draw(disk, s, d);
}

void solve(int k, Rod &src, Rod &aux, Rod &dst, char s, char a, char d) {
    if (k == 1) { move(src, dst, s, d); return; }
    solve(k - 1, src, dst, aux, s, d, a);
    move(src, dst, s, d);
    solve(k - 1, aux, src, dst, a, s, d);
}

int main() {
    cout << "Enter number of disks (1-8): ";
    cin >> n;
    if (n < 1 || n > 8) n = 3;

    cout << "Speed — 1=fast  2=medium  3=slow: ";
    int speed; cin >> speed;
    if      (speed == 1) delayLoop = 30000000LL;
    else if (speed == 3) delayLoop = 300000000LL;
    else                 delayLoop = 120000000LL;

    for (int i = n; i >= 1; i--) A.push(i);

    draw();

    cout << "Press ENTER to start...";
    cin.ignore(); cin.get();

    solve(n, A, B, C, 'A', 'B', 'C');

    cout << "=====================================\n";
    cout << "  SOLVED IN " << moves << " MOVES!\n";
    cout << "=====================================\n";
    return 0;
}
