#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;




const int   MAX      = 8;
const float ROD_X[3] = {200.f, 500.f, 800.f};
const float BASE_Y   = 500.f;
const float ROD_H    = 300.f;
const float DISK_H   = 25.f;

struct Stack {
    int arr[MAX];
    int top = -1;

    void push(int v) { if (top < MAX - 1) arr[++top] = v; }
    int  pop()       { return top < 0 ? 0 : arr[top--]; }
    int  size()      { return top + 1; }
    int  at(int i)   { return (i >= 0 && i <= top) ? arr[i] : 0; }
    void clear()     { top = -1; }
};

Stack rod[3];
int totalDisks, moveCount;
bool isPaused = false;

void checkEvents(sf::RenderWindow& win) {
    sf::Event e;
    while (win.pollEvent(e)) {
        if (e.type == sf::Event::Closed) win.close();
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space)
            isPaused = !isPaused;
    }
    while (isPaused && win.isOpen()) {
        sf::Event pe;
        while (win.pollEvent(pe)) {
            if (pe.type == sf::Event::Closed) win.close();
            if (pe.type == sf::Event::KeyPressed && pe.key.code == sf::Keyboard::Space)
                isPaused = false;
        }
    }
}

void resetPuzzle() {
    moveCount = 0;
    for (int i = 0; i < 3; i++) rod[i].clear();
    for (int i = totalDisks; i >= 1; i--) rod[0].push(i);
}

void drawScene(sf::RenderWindow& win) {
    win.clear(sf::Color::Black);

    sf::RectangleShape base(sf::Vector2f(900.f, 20.f));
    base.setPosition(50.f, BASE_Y);
    base.setFillColor(sf::Color::White);
    win.draw(base);

    for (int i = 0; i < 3; i++) {
        sf::RectangleShape r(sf::Vector2f(10.f, ROD_H));
        r.setPosition(ROD_X[i] - 5.f, BASE_Y - ROD_H);
        r.setFillColor(sf::Color::White);
        win.draw(r);
    }

    for (int r = 0; r < 3; r++) {
        for (int lvl = 0; lvl < rod[r].size(); lvl++) {
            int d = rod[r].at(lvl);
            float w = 50.f + d * 20.f;
            sf::RectangleShape disk(sf::Vector2f(w, 20.f));
            disk.setOrigin(w / 2.f, 0.f);
            disk.setPosition(ROD_X[r], BASE_Y - (lvl + 1) * DISK_H);
            disk.setFillColor(sf::Color::Cyan);
            disk.setOutlineThickness(1.f);
            disk.setOutlineColor(sf::Color::White);
            win.draw(disk);
        }
    }
}

void animateMove(sf::RenderWindow& win, int src, int dst) {
    if (!win.isOpen()) return;

    int d = rod[src].pop();
    moveCount++;
    cout << "Move " << moveCount << ": disk " << d
         << "  [" << (char)('A' + src) << " -> " << (char)('A' + dst) << "]\n";

    float sx = ROD_X[src], sy = BASE_Y - (rod[src].size() + 1) * DISK_H;
    float tx = ROD_X[dst], ty = BASE_Y - (rod[dst].size() + 1) * DISK_H;
    float peakY = BASE_Y - ROD_H - 50.f;

    float w = 50.f + d * 20.f;
    sf::RectangleShape disk(sf::Vector2f(w, 20.f));
    disk.setOrigin(w / 2.f, 0.f);
    disk.setFillColor(sf::Color::Cyan);
    disk.setOutlineThickness(1.f);
    disk.setOutlineColor(sf::Color::White);

    sf::Clock clk;
    float phase = 0.3f;

    clk.restart();
    while (clk.getElapsedTime().asSeconds() < phase && win.isOpen()) {
        checkEvents(win);
        float p = clk.getElapsedTime().asSeconds() / phase;
        disk.setPosition(sx, sy + (peakY - sy) * p);
        drawScene(win); win.draw(disk); win.display();
    }

    clk.restart();
    while (clk.getElapsedTime().asSeconds() < phase && win.isOpen()) {
        checkEvents(win);
        float p = clk.getElapsedTime().asSeconds() / phase;
        disk.setPosition(sx + (tx - sx) * p, peakY);
        drawScene(win); win.draw(disk); win.display();
    }

    clk.restart();
    while (clk.getElapsedTime().asSeconds() < phase && win.isOpen()) {
        checkEvents(win);
        float p = clk.getElapsedTime().asSeconds() / phase;
        disk.setPosition(tx, peakY + (ty - peakY) * p);
        drawScene(win); win.draw(disk); win.display();
    }

    rod[dst].push(d);
}

void solve(sf::RenderWindow& win, int n, int src, int aux, int dst) {
    if (n < 1 || !win.isOpen()) return;
    solve(win, n - 1, src, dst, aux);
    animateMove(win, src, dst);
    solve(win, n - 1, aux, src, dst);
}

int main() {
    cout << "Enter number of disks (1-8): ";
    cin >> totalDisks;
    if (totalDisks < 1 || totalDisks > 8) {
        cout << "Invalid. Using 4.\n";
        totalDisks = 4;
    }

    sf::RenderWindow win(sf::VideoMode(1000, 600), "Tower of Hanoi");
    win.setFramerateLimit(60);

    resetPuzzle();
    cout << "Press SPACE to start/pause...\n";

    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) win.close();
            if (e.type == sf::Event::KeyPressed &&
                e.key.code == sf::Keyboard::Space) goto start;
        }
        drawScene(win);
        win.display();
    }

start:
    solve(win, totalDisks, 0, 1, 2);
    cout << "Solved in " << moveCount << " moves!\n";

    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) if (e.type == sf::Event::Closed) win.close();
        drawScene(win);
        win.display();
    }

    return 0;
}
