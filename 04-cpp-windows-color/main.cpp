#include <iostream>
#include <windows.h>
using namespace std;

const int MAX = 10;

// Array-based rod stack — built from scratch
struct Peg {
    int d[MAX];
    int top = -1;

    void push(int v)    { if (top < MAX - 1) d[++top] = v; }
    int  pop()          { return (top == -1) ? 0 : d[top--]; }
    bool isEmpty()      { return top == -1; }
    int  diskAt(int lvl){ return (lvl >= 0 && lvl <= top) ? d[lvl] : 0; }
};

Peg A, B, C;
int n;
int step = 0;
int delayMs = 500;

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void repeat(char ch, int times) {
    for (int i = 0; i < times; i++) cout << ch;
}

void draw(int moved = 0, char from = ' ', char to = ' ') {
    system("cls");

    color(14);
    cout << "======================================================\n";
    cout << "         TOWER OF HANOI  (Windows Color Console)      \n";
    cout << "======================================================\n\n";

    color(15);
    if (step == 0)
        cout << " Initial: " << n << " disks on Rod A\n\n";
    else
        cout << " Step " << step << ":  Disk [" << moved << "]  " << from << " -> " << to << "\n\n";

    int fw = n * 2 + 3;  // field width per rod

    for (int lvl = n - 1; lvl >= 0; lvl--) {
        Peg* rods[3] = { &A, &B, &C };
        for (int r = 0; r < 3; r++) {
            int ds = rods[r]->diskAt(lvl);
            int sp = (fw - (ds > 0 ? ds * 2 + 1 : 1)) / 2;
            repeat(' ', sp);
            if (ds > 0) {
                color(9 + (ds % 6));
                cout << '<';
                repeat('=', ds - 1);
                cout << ds;
                repeat('=', ds - 1);
                cout << '>';
            } else {
                color(8); cout << '|';
            }
            color(15);
            repeat(' ', sp + 4);
        }
        cout << '\n';
    }

    color(7);
    for (int i = 0; i < 3; i++) { repeat('=', fw); cout << "    "; }
    cout << '\n';

    int pad = fw / 2;
    color(11);
    repeat(' ', pad); cout << "ROD A"; repeat(' ', pad + 4);
    repeat(' ', pad); cout << "ROD B"; repeat(' ', pad + 4);
    repeat(' ', pad); cout << "ROD C\n\n";

    color(15);
    Sleep(delayMs);
}

void move(Peg &src, Peg &dst, char from, char to) {
    int disk = src.pop();
    dst.push(disk);
    step++;
    draw(disk, from, to);
}

void solve(int k, Peg &src, Peg &aux, Peg &dst, char s, char a, char d) {
    if (k == 1) { move(src, dst, s, d); return; }
    solve(k - 1, src, dst, aux, s, d, a);
    move(src, dst, s, d);
    solve(k - 1, aux, src, dst, a, s, d);
}

int main() {
    color(14);
    cout << "Enter number of disks (1-8): ";
    color(15); cin >> n;
    if (n < 1 || n > 8) n = 3;

    color(14);
    cout << "Speed — 1=fast  2=medium  3=slow: ";
    color(15);
    int sp; cin >> sp;
    if      (sp == 1) delayMs = 200;
    else if (sp == 3) delayMs = 900;
    else              delayMs = 500;

    for (int i = n; i >= 1; i--) A.push(i);

    draw();

    color(10);
    cout << "Press ENTER to start...";
    cin.ignore(); cin.get();

    solve(n, A, B, C, 'A', 'B', 'C');

    color(10);
    cout << "\nSOLVED IN " << step << " MOVES!\n\n";
    color(15);
    return 0;
}
