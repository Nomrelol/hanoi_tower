#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// Maximum disk capacity supported
const int MAX_DISKS = 8;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 650;

// Custom Stack Structure (Built from scratch: NO STL vector/stack used)
struct Stack {
    int arr[MAX_DISKS];
    int top = -1;

    void push(int disk) {
        if (top < MAX_DISKS - 1) {
            arr[++top] = disk;
        }
    }

    int pop() {
        if (top == -1) return 0;
        return arr[top--];
    }

    int peek() {
        if (top == -1) return 0;
        return arr[top];
    }

    bool isEmpty() { return top == -1; }
    int getSize() { return top + 1; }
    int getAt(int level) {
        if (level >= 0 && level <= top) return arr[level];
        return 0;
    }
    void clear() { top = -1; }
};

// Rod Base Geometry
const float ROD_X[3] = { 220.f, 500.f, 780.f };
const float BASE_Y = 520.f;
const float ROD_HEIGHT = 280.f;
const float DISK_HEIGHT = 26.f;

// Global Game State
Stack rodA, rodB, rodC;
int totalDisks = 4;
int stepCounter = 0;
int moveSpeedMs = 300; // Animation speed in milliseconds
bool isPaused = false;
bool stepByStepMode = false;
string statusText = "Press SPACE to start animation | UP/DOWN to change speed | R to reset";

// Vibrant Color Palette for Disks
sf::Color diskPalette[8] = {
    sf::Color(231, 76, 60),   // Red (Disk 1)
    sf::Color(230, 126, 34),  // Orange (Disk 2)
    sf::Color(241, 196, 15),  // Yellow (Disk 3)
    sf::Color(46, 204, 113),  // Green (Disk 4)
    sf::Color(52, 152, 219),  // Blue (Disk 5)
    sf::Color(155, 89, 182),  // Purple (Disk 6)
    sf::Color(26, 188, 156),  // Teal (Disk 7)
    sf::Color(52, 73, 94)     // Slate (Disk 8)
};

// Smoothstep Ease-In-Out Interpolation Curve for Realistic Motion Physics
float smoothstep(float edge0, float edge1, float x) {
    float t = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

// Function to render full SFML graphic scene
void renderScene(sf::RenderWindow &window, sf::Font &font) {
    window.clear(sf::Color(24, 26, 36)); // Dark sleek background

    // 1. Draw Base Platform
    sf::RectangleShape base(sf::Vector2f(900.f, 22.f));
    base.setPosition(50.f, BASE_Y);
    base.setFillColor(sf::Color(100, 105, 120));
    window.draw(base);

    // 2. Draw 3 Vertical Rods & Labels
    char rodNames[3] = { 'A', 'B', 'C' };
    for (int i = 0; i < 3; i++) {
        sf::RectangleShape rod(sf::Vector2f(14.f, ROD_HEIGHT));
        rod.setPosition(ROD_X[i] - 7.f, BASE_Y - ROD_HEIGHT);
        rod.setFillColor(sf::Color(170, 175, 190));
        window.draw(rod);

        sf::Text label;
        label.setFont(font);
        label.setString(string("ROD ") + rodNames[i]);
        label.setCharacterSize(22);
        label.setStyle(sf::Text::Bold);
        label.setFillColor(sf::Color(241, 196, 15));
        label.setPosition(ROD_X[i] - 32.f, BASE_Y + 30.f);
        window.draw(label);
    }

    // 3. Draw Disks on Stacks
    Stack* rods[3] = { &rodA, &rodB, &rodC };
    for (int r = 0; r < 3; r++) {
        int count = rods[r]->getSize();
        for (int level = 0; level < count; level++) {
            int diskSize = rods[r]->getAt(level);
            if (diskSize > 0) {
                float diskWidth = 45.f + (diskSize * 24.f);
                sf::RectangleShape disk(sf::Vector2f(diskWidth, DISK_HEIGHT - 3.f));
                disk.setOrigin(diskWidth / 2.f, 0.f);
                disk.setPosition(ROD_X[r], BASE_Y - ((level + 1) * DISK_HEIGHT));
                disk.setFillColor(diskPalette[(diskSize - 1) % 8]);
                disk.setOutlineThickness(1.5f);
                disk.setOutlineColor(sf::Color(255, 255, 255, 200));
                window.draw(disk);

                // Disk Number Text
                sf::Text diskNum;
                diskNum.setFont(font);
                diskNum.setString(to_string(diskSize));
                diskNum.setCharacterSize(14);
                diskNum.setFillColor(sf::Color::White);
                diskNum.setPosition(ROD_X[r] - 4.f, BASE_Y - ((level + 1) * DISK_HEIGHT) + 2.f);
                window.draw(diskNum);
            }
        }
    }

    // 4. Draw Header & Control HUD Text
    sf::Text title;
    title.setFont(font);
    title.setString("TOWER OF HANOI - SFML 2D ENGINE");
    title.setCharacterSize(24);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition(300.f, 15.f);
    window.draw(title);

    // Status Panel
    sf::Text status;
    status.setFont(font);
    status.setString("Step: " + to_string(stepCounter) + " / " + to_string((1 << totalDisks) - 1) + 
                     " | Speed: " + to_string(moveSpeedMs) + "ms | " + statusText);
    status.setCharacterSize(17);
    status.setFillColor(sf::Color(220, 220, 220));
    status.setPosition(50.f, 55.f);
    window.draw(status);

    // Rule Legend Panel at Bottom
    sf::Text legend;
    legend.setFont(font);
    legend.setString("Rules: 1. Only 1 disk moved at a time  |  2. Larger disk cannot go on smaller disk");
    legend.setCharacterSize(15);
    legend.setFillColor(sf::Color(160, 165, 180));
    legend.setPosition(180.f, WINDOW_HEIGHT - 35.f);
    window.draw(legend);

    window.display();
}

// Handle Window Event Loop during animations
void processEvents(sf::RenderWindow &window) {
    sf::Event ev;
    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) {
            window.close();
        }
        if (ev.type == sf::Event::KeyPressed) {
            if (ev.key.code == sf::Keyboard::Space) {
                isPaused = !isPaused;
            }
            if (ev.key.code == sf::Keyboard::Up) {
                if (moveSpeedMs > 50) moveSpeedMs -= 50;
            }
            if (ev.key.code == sf::Keyboard::Down) {
                if (moveSpeedMs < 1000) moveSpeedMs += 50;
            }
        }
    }
}

// Smoothly animate disk moving from source rod to destination rod
void animateMove(sf::RenderWindow &window, sf::Font &font, Stack &src, Stack &dest,
                 int srcIdx, int destIdx, char fromRod, char toRod) {
    if (!window.isOpen()) return;

    // Rule Validation Check
    if (!dest.isEmpty() && src.peek() > dest.peek()) {
        statusText = "[ERROR]: Illegal move! Larger disk cannot be placed on smaller disk.";
        return;
    }

    int diskSize = src.pop();
    stepCounter++;
    statusText = "Moved Disk [" + to_string(diskSize) + "] from Rod " + fromRod + " to Rod " + toRod;

    float diskWidth = 45.f + (diskSize * 24.f);
    float startX = ROD_X[srcIdx];
    float startY = BASE_Y - ((src.getSize() + 1) * DISK_HEIGHT);
    float targetX = ROD_X[destIdx];
    float targetY = BASE_Y - ((dest.getSize() + 1) * DISK_HEIGHT);
    float peakY = BASE_Y - ROD_HEIGHT - 40.f;

    sf::RectangleShape animatedDisk(sf::Vector2f(diskWidth, DISK_HEIGHT - 3.f));
    animatedDisk.setOrigin(diskWidth / 2.f, 0.f);
    animatedDisk.setFillColor(diskPalette[(diskSize - 1) % 8]);
    animatedDisk.setOutlineThickness(1.5f);
    animatedDisk.setOutlineColor(sf::Color::White);

    sf::Clock clock;
    float duration = moveSpeedMs / 1000.f;

    // Phase 1: Lift Up
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < duration / 3.f && window.isOpen()) {
        processEvents(window);
        while (isPaused && window.isOpen()) processEvents(window);

        float progress = clock.getElapsedTime().asSeconds() / (duration / 3.f);
        float easeP = smoothstep(0.0f, 1.0f, progress);
        float currY = startY + (peakY - startY) * easeP;

        animatedDisk.setPosition(startX, currY);
        renderScene(window, font);
        window.draw(animatedDisk);
        window.display();
    }

    // Phase 2: Slide Horizontally
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < duration / 3.f && window.isOpen()) {
        processEvents(window);
        while (isPaused && window.isOpen()) processEvents(window);

        float progress = clock.getElapsedTime().asSeconds() / (duration / 3.f);
        float easeP = smoothstep(0.0f, 1.0f, progress);
        float currX = startX + (targetX - startX) * easeP;

        animatedDisk.setPosition(currX, peakY);
        renderScene(window, font);
        window.draw(animatedDisk);
        window.display();
    }

    // Phase 3: Drop Down
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < duration / 3.f && window.isOpen()) {
        processEvents(window);
        while (isPaused && window.isOpen()) processEvents(window);

        float progress = clock.getElapsedTime().asSeconds() / (duration / 3.f);
        float easeP = smoothstep(0.0f, 1.0f, progress);
        float currY = peakY + (targetY - peakY) * easeP;

        animatedDisk.setPosition(targetX, currY);
        renderScene(window, font);
        window.draw(animatedDisk);
        window.display();
    }

    dest.push(diskSize);
    renderScene(window, font);
}

// Recursive Tower of Hanoi Engine
void solveHanoiSFML(sf::RenderWindow &window, sf::Font &font, int n, 
                    Stack &src, Stack &aux, Stack &dest,
                    int sIdx, int aIdx, int dIdx,
                    char sName, char aName, char dName) {
    if (!window.isOpen()) return;

    if (n == 1) {
        animateMove(window, font, src, dest, sIdx, dIdx, sName, dName);
        return;
    }

    solveHanoiSFML(window, font, n - 1, src, dest, aux, sIdx, dIdx, aIdx, sName, dName, aName);
    animateMove(window, font, src, dest, sIdx, dIdx, sName, dName);
    solveHanoiSFML(window, font, n - 1, aux, src, dest, aIdx, sIdx, dIdx, aName, sName, dName);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tower of Hanoi - SFML 2D Visualizer");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/calibri.ttf");
    }

    cout << "Enter number of disks (1 to 8, default 4): ";
    if (!(cin >> totalDisks) || totalDisks < 1 || totalDisks > 8) {
        totalDisks = 4;
    }

    // Initialize Rod A with disks
    for (int i = totalDisks; i >= 1; i--) {
        rodA.push(i);
    }

    bool started = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (!started && (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)) {
                    started = true;
                    solveHanoiSFML(window, font, totalDisks, rodA, rodB, rodC, 0, 1, 2, 'A', 'B', 'C');
                    statusText = "PUZZLE SOLVED IN " + to_string(stepCounter) + " MOVES!";
                }
            }
        }

        renderScene(window, font);
    }

    return 0;
}
