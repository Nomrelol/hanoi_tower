#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

const int MAX_DISKS = 8;
const int WINDOW_WIDTH = 850;
const int WINDOW_HEIGHT = 550;

// Custom Stack Structure (No STL libraries used)
struct RodStack {
    int disks[MAX_DISKS];
    int top = -1;

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
    int getSize() { return top + 1; }
    int getDiskAt(int level) {
        if (level >= 0 && level <= top) return disks[level];
        return 0;
    }
};

// Global State
RodStack rodA, rodB, rodC;
int totalDisks = 4;
int stepCounter = 0;
string statusMessage = "Press SPACEBAR to start desktop window animation!";
bool isSolving = false;

// Rod Coordinates
const int ROD_X[3] = { 200, 425, 650 };
const int BASE_Y = 420;
const int ROD_HEIGHT = 240;
const int DISK_HEIGHT = 22;

// Disk Color Palette (Win32 RGB)
COLORREF diskRGB[8] = {
    RGB(231, 76, 60),   // Red (Disk 1)
    RGB(230, 126, 34),  // Orange (Disk 2)
    RGB(241, 196, 15),  // Yellow (Disk 3)
    RGB(46, 204, 113),  // Green (Disk 4)
    RGB(52, 152, 219),  // Light Blue (Disk 5)
    RGB(155, 89, 182),  // Purple (Disk 6)
    RGB(26, 188, 156),  // Teal (Disk 7)
    RGB(52, 73, 94)     // Slate (Disk 8)
};

// Function to draw scene using GDI (Double-buffered to prevent flicker)
void DrawScene(HDC hdc) {
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBitmap = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
    SelectObject(memDC, memBitmap);

    // 1. Fill Background
    HBRUSH bgBrush = CreateSolidBrush(RGB(30, 30, 42));
    RECT bgRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    FillRect(memDC, &bgRect, bgBrush);
    DeleteObject(bgBrush);

    // 2. Draw Base Platform
    HBRUSH baseBrush = CreateSolidBrush(RGB(120, 125, 140));
    RECT baseRect = { 50, BASE_Y, 800, BASE_Y + 15 };
    FillRect(memDC, &baseRect, baseBrush);
    DeleteObject(baseBrush);

    // 3. Draw Rods and Labels
    HBRUSH rodBrush = CreateSolidBrush(RGB(180, 185, 200));
    SetBkMode(memDC, TRANSPARENT);
    SetTextColor(memDC, RGB(241, 196, 15));

    char rodNames[3] = { 'A', 'B', 'C' };
    for (int i = 0; i < 3; i++) {
        RECT rRect = { ROD_X[i] - 6, BASE_Y - ROD_HEIGHT, ROD_X[i] + 6, BASE_Y };
        FillRect(memDC, &rRect, rodBrush);

        string label = string("ROD ") + rodNames[i];
        TextOutA(memDC, ROD_X[i] - 20, BASE_Y + 25, label.c_str(), (int)label.length());
    }
    DeleteObject(rodBrush);

    // 4. Draw Disks on Stacks
    RodStack* rods[3] = { &rodA, &rodB, &rodC };
    for (int r = 0; r < 3; r++) {
        int count = rods[r]->getSize();
        for (int level = 0; level < count; level++) {
            int diskSize = rods[r]->getDiskAt(level);
            if (diskSize > 0) {
                int diskWidth = 36 + (diskSize * 22);
                int left = ROD_X[r] - (diskWidth / 2);
                int topPos = BASE_Y - ((level + 1) * DISK_HEIGHT);
                int right = left + diskWidth;
                int bottom = topPos + DISK_HEIGHT - 2;

                HBRUSH dBrush = CreateSolidBrush(diskRGB[(diskSize - 1) % 8]);
                RECT dRect = { left, topPos, right, bottom };
                FillRect(memDC, &dRect, dBrush);
                DeleteObject(dBrush);

                // Draw outline around disk
                HPEN borderPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
                HPEN oldPen = (HPEN)SelectObject(memDC, borderPen);
                HBRUSH nullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
                HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, nullBrush);
                Rectangle(memDC, left, topPos, right, bottom);
                SelectObject(memDC, oldPen);
                SelectObject(memDC, oldBrush);
                DeleteObject(borderPen);
            }
        }
    }

    // 5. Draw Header HUD Text
    SetTextColor(memDC, RGB(52, 152, 219));
    string title = "TOWER OF HANOI - NATIVE WIN32 GUI VISUALIZER";
    TextOutA(memDC, 220, 20, title.c_str(), (int)title.length());

    SetTextColor(memDC, RGB(255, 255, 255));
    string hud = "Step: " + to_string(stepCounter) + " | " + statusMessage;
    TextOutA(memDC, 50, 55, hud.c_str(), (int)hud.length());

    // Copy memory DC to screen DC
    BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, memDC, 0, 0, SRCCOPY);

    DeleteObject(memBitmap);
    DeleteDC(memDC);
}

// Window Procedure Callback
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            DrawScene(hdc);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_KEYDOWN: {
            if (wParam == VK_SPACE && !isSolving) {
                isSolving = true;
                statusMessage = "Animation Running...";
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Move Disk helper function with window redraw & delay
void MoveDiskWin32(HWND hwnd, RodStack &src, RodStack &dest, char sName, char dName) {
    int disk = src.pop();
    dest.push(disk);
    stepCounter++;
    statusMessage = "Moved Disk [" + to_string(disk) + "] from Rod " + sName + " to Rod " + dName;

    HDC hdc = GetDC(hwnd);
    DrawScene(hdc);
    ReleaseDC(hwnd, hdc);

    Sleep(500); // 0.5s pause per move step
}

// Recursive Solver
void SolveHanoiWin32(HWND hwnd, int n, RodStack &src, RodStack &aux, RodStack &dest, char s, char a, char d) {
    if (n == 1) {
        MoveDiskWin32(hwnd, src, dest, s, d);
        return;
    }
    SolveHanoiWin32(hwnd, n - 1, src, dest, aux, s, d, a);
    MoveDiskWin32(hwnd, src, dest, s, d);
    SolveHanoiWin32(hwnd, n - 1, aux, src, dest, a, s, d);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    totalDisks = 4;
    for (int i = totalDisks; i >= 1; i--) rodA.push(i);

    // Register Window Class
    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "HanoiWin32Class";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassA(&wc);

    // Create Window
    HWND hwnd = CreateWindowA(
        "HanoiWin32Class", "Tower of Hanoi - Win32 Native GUI",
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Main Message Loop
    MSG msg;
    bool solverStarted = false;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (isSolving && !solverStarted) {
            solverStarted = true;
            SolveHanoiWin32(hwnd, totalDisks, rodA, rodB, rodC, 'A', 'B', 'C');
            statusMessage = "SOLVED SUCCESSFULLY IN " + to_string(stepCounter) + " MOVES!";
            HDC hdc = GetDC(hwnd);
            DrawScene(hdc);
            ReleaseDC(hwnd, hdc);
        }
    }

    return (int)msg.wParam;
}
