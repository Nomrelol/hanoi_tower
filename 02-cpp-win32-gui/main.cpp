#include <windows.h>
#include <iostream>
using namespace std;

const int MAX_DISKS   = 8;
const int WIN_W       = 850;
const int WIN_H       = 550;
const int ROD_X[3]    = { 200, 425, 650 };
const int BASE_Y      = 420;
const int ROD_H       = 240;
const int DISK_H      = 22;

// Array-based stack — built from scratch
struct Tower {
    int d[MAX_DISKS];
    int top = -1;

    void push(int v)      { if (top < MAX_DISKS - 1) d[++top] = v; }
    int  pop()            { return (top == -1) ? 0 : d[top--]; }
    int  peek()           { return (top == -1) ? 0 : d[top]; }
    bool empty()          { return top == -1; }
    int  size()           { return top + 1; }
    int  at(int lvl)      { return (lvl >= 0 && lvl <= top) ? d[lvl] : 0; }
};

Tower rodA, rodB, rodC;
int   totalDisks  = 4;
int   stepCount   = 0;
int   delayMs     = 600;   // adjustable with UP/DOWN keys
bool  running     = false;
char  statusMsg[128] = "Press SPACEBAR to start animation";

COLORREF diskColor[8] = {
    RGB(231, 76,  60),   // red
    RGB(230, 126, 34),   // orange
    RGB(241, 196, 15),   // yellow
    RGB(46,  204, 113),  // green
    RGB(52,  152, 219),  // blue
    RGB(155, 89,  182),  // purple
    RGB(26,  188, 156),  // teal
    RGB(52,  73,  94)    // slate
};

void paint(HDC hdc) {
    // Double-buffer to stop flicker
    HDC     mem  = CreateCompatibleDC(hdc);
    HBITMAP bmp  = CreateCompatibleBitmap(hdc, WIN_W, WIN_H);
    SelectObject(mem, bmp);

    // Background
    RECT bg = { 0, 0, WIN_W, WIN_H };
    HBRUSH br = CreateSolidBrush(RGB(28, 30, 42));
    FillRect(mem, &bg, br); DeleteObject(br);

    // Base platform
    br = CreateSolidBrush(RGB(110, 115, 130));
    RECT base = { 50, BASE_Y, 800, BASE_Y + 14 };
    FillRect(mem, &base, br); DeleteObject(br);

    SetBkMode(mem, TRANSPARENT);
    char rodNames[3] = { 'A', 'B', 'C' };
    br = CreateSolidBrush(RGB(175, 180, 195));

    for (int i = 0; i < 3; i++) {
        // Rod
        RECT rod = { ROD_X[i] - 6, BASE_Y - ROD_H, ROD_X[i] + 6, BASE_Y };
        FillRect(mem, &rod, br);

        // Label
        char lbl[8]; sprintf(lbl, "ROD %c", rodNames[i]);
        SetTextColor(mem, RGB(241, 196, 15));
        TextOutA(mem, ROD_X[i] - 18, BASE_Y + 24, lbl, 5);
    }
    DeleteObject(br);

    // Disks
    Tower* rods[3] = { &rodA, &rodB, &rodC };
    for (int r = 0; r < 3; r++) {
        for (int lvl = 0; lvl < rods[r]->size(); lvl++) {
            int ds = rods[r]->at(lvl);
            if (ds == 0) continue;
            int w  = 36 + ds * 22;
            int lx = ROD_X[r] - w / 2;
            int ty = BASE_Y - (lvl + 1) * DISK_H;
            RECT dr = { lx, ty, lx + w, ty + DISK_H - 2 };
            br = CreateSolidBrush(diskColor[(ds - 1) % 8]);
            FillRect(mem, &dr, br); DeleteObject(br);
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            HPEN op  = (HPEN)SelectObject(mem, pen);
            HBRUSH ob = (HBRUSH)SelectObject(mem, GetStockObject(NULL_BRUSH));
            Rectangle(mem, lx, ty, lx + w, ty + DISK_H - 2);
            SelectObject(mem, op); SelectObject(mem, ob); DeleteObject(pen);
        }
    }

    // HUD
    SetTextColor(mem, RGB(52, 152, 219));
    const char* title = "TOWER OF HANOI - NATIVE WIN32 GUI";
    TextOutA(mem, 260, 18, title, (int)strlen(title));

    char hud[128]; sprintf(hud, "Step: %d  |  Speed: %dms  |  UP/DOWN keys to adjust", stepCount, delayMs);
    SetTextColor(mem, RGB(255, 255, 255));
    TextOutA(mem, 50, 52, hud, (int)strlen(hud));

    SetTextColor(mem, RGB(241, 196, 15));
    TextOutA(mem, 50, 78, statusMsg, (int)strlen(statusMsg));

    BitBlt(hdc, 0, 0, WIN_W, WIN_H, mem, 0, 0, SRCCOPY);
    DeleteObject(bmp); DeleteDC(mem);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            paint(hdc);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_KEYDOWN:
            if (wp == VK_SPACE && !running) {
                running = true;
                strcpy(statusMsg, "Animation running...");
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if (wp == VK_UP   && delayMs > 100) { delayMs -= 100; }
            if (wp == VK_DOWN && delayMs < 1500) { delayMs += 100; }
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case WM_DESTROY:
            PostQuitMessage(0); break;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

void moveDisk(HWND hwnd, Tower &src, Tower &dst, char from, char to) {
    int disk = src.pop();
    dst.push(disk);
    stepCount++;
    sprintf(statusMsg, "Moved Disk [%d]  %c -> %c", disk, from, to);
    HDC hdc = GetDC(hwnd);
    paint(hdc);
    ReleaseDC(hwnd, hdc);
    Sleep(delayMs);
}

void solve(HWND hwnd, int k, Tower &src, Tower &aux, Tower &dst, char s, char a, char d) {
    if (k == 1) { moveDisk(hwnd, src, dst, s, d); return; }
    solve(hwnd, k - 1, src, dst, aux, s, d, a);
    moveDisk(hwnd, src, dst, s, d);
    solve(hwnd, k - 1, aux, src, dst, a, s, d);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int show) {
    // Ask disk count in the console before opening window
    AllocConsole();
    FILE *fp; freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$",  "r", stdin);
    cout << "Enter number of disks (1-8): ";
    cin  >> totalDisks;
    if (totalDisks < 1 || totalDisks > 8) totalDisks = 4;
    FreeConsole();

    for (int i = totalDisks; i >= 1; i--) rodA.push(i);
    sprintf(statusMsg, "Press SPACEBAR to start  |  Disks: %d  |  UP/DOWN to adjust speed", totalDisks);

    WNDCLASSA wc  = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = "HanoiClass";
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowA("HanoiClass", "Tower of Hanoi - Win32 GUI",
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, WIN_W, WIN_H, NULL, NULL, hInst, NULL);
    ShowWindow(hwnd, show);
    UpdateWindow(hwnd);

    MSG msg;
    bool started = false;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (running && !started) {
            started = true;
            solve(hwnd, totalDisks, rodA, rodB, rodC, 'A', 'B', 'C');
            sprintf(statusMsg, "SOLVED IN %d MOVES! Press R to quit.", stepCount);
            HDC hdc = GetDC(hwnd); paint(hdc); ReleaseDC(hwnd, hdc);
        }
    }
    return (int)msg.wParam;
}
