#include <windows.h>
#include <cstdio>
#include <cstring>

const int MAX_DISKS = 8;
const int WIN_W     = 850;
const int WIN_H     = 550;
const int ROD_X[3]  = { 200, 425, 650 };
const int BASE_Y    = 420;
const int ROD_H     = 240;
const int DISK_H    = 22;

// Array-based stack — built from scratch, no STL
struct Tower {
    int  d[MAX_DISKS];
    int  top = -1;

    void push(int v)  { if (top < MAX_DISKS - 1) d[++top] = v; }
    int  pop()        { return (top == -1) ? 0 : d[top--]; }
    bool empty()      { return top == -1; }
    int  size()       { return top + 1; }
    int  at(int lvl)  { return (lvl >= 0 && lvl <= top) ? d[lvl] : 0; }
};

Tower rodA, rodB, rodC;
int   totalDisks = 4;
int   stepCount  = 0;
int   delayMs    = 600;
bool  running    = false;
bool  solved     = false;
char  statusMsg[160] = "Keys 1-8: change disks  |  SPACE: start  |  UP/DOWN: speed";

COLORREF diskColor[8] = {
    RGB(231, 76,  60),
    RGB(230, 126, 34),
    RGB(241, 196, 15),
    RGB(46,  204, 113),
    RGB(52,  152, 219),
    RGB(155, 89,  182),
    RGB(26,  188, 156),
    RGB(52,  73,  94)
};

// Reset rods to initial state
void reset(int n) {
    totalDisks = n;
    stepCount  = 0;
    running    = false;
    solved     = false;
    rodA.top = rodB.top = rodC.top = -1;
    for (int i = n; i >= 1; i--) rodA.push(i);
    sprintf(statusMsg, "Disks: %d  |  Keys 1-8: change  |  SPACE: start  |  UP/DOWN: speed", n);
}

void paint(HDC hdc) {
    HDC     mem = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateCompatibleBitmap(hdc, WIN_W, WIN_H);
    SelectObject(mem, bmp);

    // Background
    RECT bg = { 0, 0, WIN_W, WIN_H };
    HBRUSH br = CreateSolidBrush(RGB(28, 30, 42));
    FillRect(mem, &bg, br); DeleteObject(br);

    // Base platform
    br = CreateSolidBrush(RGB(110, 115, 130));
    RECT base = { 50, BASE_Y, 800, BASE_Y + 14 };
    FillRect(mem, &base, br); DeleteObject(br);

    // Rods and labels
    SetBkMode(mem, TRANSPARENT);
    char rodNames[3] = { 'A', 'B', 'C' };
    br = CreateSolidBrush(RGB(175, 180, 195));
    for (int i = 0; i < 3; i++) {
        RECT rod = { ROD_X[i] - 6, BASE_Y - ROD_H, ROD_X[i] + 6, BASE_Y };
        FillRect(mem, &rod, br);
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
            HPEN  op = (HPEN)SelectObject(mem, pen);
            HBRUSH ob = (HBRUSH)SelectObject(mem, GetStockObject(NULL_BRUSH));
            Rectangle(mem, lx, ty, lx + w, ty + DISK_H - 2);
            SelectObject(mem, op); SelectObject(mem, ob); DeleteObject(pen);
        }
    }

    // HUD text
    SetTextColor(mem, RGB(52, 152, 219));
    const char* title = "TOWER OF HANOI - NATIVE WIN32 GUI";
    TextOutA(mem, 260, 18, title, (int)strlen(title));

    char hud[128];
    sprintf(hud, "Step: %d  |  Speed: %dms", stepCount, delayMs);
    SetTextColor(mem, RGB(255, 255, 255));
    TextOutA(mem, 50, 52, hud, (int)strlen(hud));

    SetTextColor(mem, RGB(241, 196, 15));
    TextOutA(mem, 50, 78, statusMsg, (int)strlen(statusMsg));

    BitBlt(hdc, 0, 0, WIN_W, WIN_H, mem, 0, 0, SRCCOPY);
    DeleteObject(bmp);
    DeleteDC(mem);
}

HWND g_hwnd = NULL;  // global handle for safe access during solve

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            paint(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_KEYDOWN:
            if (!running) {
                // 1-8 keys select disk count
                if (wp >= '1' && wp <= '8') {
                    reset((int)(wp - '0'));
                    InvalidateRect(hwnd, NULL, FALSE);
                }
                if (wp == VK_SPACE) {
                    running = true;
                    sprintf(statusMsg, "Animating...  |  Speed: %dms  |  UP/DOWN to adjust", delayMs);
                    InvalidateRect(hwnd, NULL, FALSE);
                }
            }
            if (wp == VK_UP   && delayMs > 100)  { delayMs -= 100; InvalidateRect(hwnd, NULL, FALSE); }
            if (wp == VK_DOWN && delayMs < 1500) { delayMs += 100; InvalidateRect(hwnd, NULL, FALSE); }
            if (wp == 'R' && !running) { reset(totalDisks); InvalidateRect(hwnd, NULL, FALSE); }
            return 0;
        case WM_DESTROY:
            g_hwnd = NULL;
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
}

// Move one disk and repaint; returns false if window was closed
bool moveDisk(Tower &src, Tower &dst, char from, char to) {
    if (!g_hwnd || !IsWindow(g_hwnd)) return false;
    int disk = src.pop();
    dst.push(disk);
    stepCount++;
    sprintf(statusMsg, "Moved Disk [%d]  %c -> %c", disk, from, to);
    HDC hdc = GetDC(g_hwnd);
    paint(hdc);
    ReleaseDC(g_hwnd, hdc);
    Sleep(delayMs);
    return true;
}

void solve(int k, Tower &src, Tower &aux, Tower &dst, char s, char a, char d) {
    if (!g_hwnd || !IsWindow(g_hwnd)) return;
    if (k == 1) { moveDisk(src, dst, s, d); return; }
    solve(k - 1, src, dst, aux, s, d, a);
    if (!moveDisk(src, dst, s, d)) return;
    solve(k - 1, aux, src, dst, a, s, d);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int show) {
    WNDCLASSA wc  = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = "HanoiWin32";
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    RegisterClassA(&wc);

    g_hwnd = CreateWindowA(
        "HanoiWin32", "Tower of Hanoi - Native Win32 GUI",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, WIN_W, WIN_H,
        NULL, NULL, hInst, NULL
    );

    reset(4);  // start with 4 disks

    ShowWindow(g_hwnd, show);
    UpdateWindow(g_hwnd);

    MSG msg;
    bool started = false;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (running && !started && !solved) {
            started = true;
            solve(totalDisks, rodA, rodB, rodC, 'A', 'B', 'C');
            if (g_hwnd && IsWindow(g_hwnd)) {
                solved = true;
                sprintf(statusMsg, "SOLVED IN %d MOVES!  Press R to reset.", stepCount);
                HDC hdc = GetDC(g_hwnd);
                paint(hdc);
                ReleaseDC(g_hwnd, hdc);
            }
        }
    }

    return (int)msg.wParam;
}
