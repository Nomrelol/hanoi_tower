#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

const int MAX_DISKS = 8;
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;

// Custom Stack Structure (No STL vector/stack used)
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
};

// Rod Screen Positions
const float ROD_X[3] = { 200.f, 450.f, 700.f };
const float BASE_Y = 500.f;
const float ROD_HEIGHT = 260.f;
const float DISK_HEIGHT = 24.f;

Stack rodA, rodB, rodC;
int totalDisks = 4;
int stepCounter = 0;
string currentActionText = "Press SPACE or ENTER in SFML window to start animation";

// Disk Colors Palette
sf::Color diskColors[8] = {
    sf::Color(231, 76, 60),   // Red (Disk 1)
    sf::Color(230, 126, 34),  // Orange (Disk 2)
    sf::Color(241, 196, 15),  // Yellow (Disk 3)
    sf::Color(46, 204, 113),  // Green (Disk 4)
    sf::Color(52, 152, 219),  // Light Blue (Disk 5)
    sf::Color(155, 89, 182),  // Purple (Disk 6)
    sf::Color(26, 188, 156),  // Teal (Disk 7)
    sf::Color(54, 75, 96)     // Slate (Disk 8)
};

// Render full SFML graphical scene
void renderScene(sf::RenderWindow &window, sf::Font &font) {
    window.clear(sf::Color(30, 30, 42)); // Dark Navy Slate background

    // 1. Draw Base Platform
    sf::RectangleShape base(sf::Vector2f(800.f, 20.f));
    base.setPosition(50.f, BASE_Y);
    base.setFillColor(sf::Color(120, 125, 140));
    window.draw(base);

    // 2. Draw 3 Vertical Rods & Labels
    char rodNames[3] = { 'A', 'B', 'C' };
    for (int i = 0; i < 3; i++) {
        sf::RectangleShape rod(sf::Vector2f(12.f, ROD_HEIGHT));
        rod.setPosition(ROD_X[i] - 6.f, BASE_Y - ROD_HEIGHT);
        rod.setFillColor(sf::Color(180, 185, 200));
        window.draw(rod);

        sf::Text label;
        label.setFont(font);
        label.setString(string("ROD ") + rodNames[i]);
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::Yellow);
        label.setPosition(ROD_X[i] - 30.f, BASE_Y + 30.f);
        window.draw(label);
    }

    // 3. Draw Disks on Stacks
    Stack* rods[3] = { &rodA, &rodB, &rodC };
    for (int r = 0; r < 3; r++) {
        int count = rods[r]->getSize();
        for (int level = 0; level < count; level++) {
            int diskSize = rods[r]->getAt(level);
            if (diskSize > 0) {
                float diskWidth = 40.f + (diskSize * 22.f);
                sf::RectangleShape disk(sf::Vector2f(diskWidth, DISK_HEIGHT - 2.f));
                disk.setOrigin(diskWidth / 2.f, 0.f);
                disk.setPosition(ROD_X[r], BASE_Y - ((level + 1) * DISK_HEIGHT));
                disk.setFillColor(diskColors[(diskSize - 1) % 8]);
                disk.setOutlineThickness(1.f);
                disk.setOutlineColor(sf::Color::White);
                window.draw(disk);
            }
        }
    }

    // 4. Draw Window Title & HUD Text
    sf::Text header;
    header.setFont(font);
    header.setString("TOWER OF HANOI - SFML GRAPHICAL ANIMATION");
    header.setCharacterSize(22);
    header.setStyle(sf::Text::Bold);
    header.setFillColor(sf::Color::Cyan);
    header.setPosition(180.f, 20.f);
    window.draw(header);

    sf::Text status;
    status.setFont(font);
    status.setString("Step: " + to_string(stepCounter) + " | " + currentActionText);
    status.setCharacterSize(18);
    status.setFillColor(sf::Color::White);
    status.setPosition(50.f, 60.f);
    window.draw(status);

    window.display();
}

// Smoothly animate disk moving from source rod to destination rod
void animateMove(sf::RenderWindow &window, sf::Font &font, Stack &src, Stack &dest,
                 int srcIdx, int destIdx, char fromRod, char toRod) {
    int diskSize = src.pop();
    stepCounter++;
    currentActionText = "Moving Disk [" + to_string(diskSize) + "] from Rod " + fromRod + " to Rod " + toRod;

    float diskWidth = 40.f + (diskSize * 22.f);
    float startX = ROD_X[srcIdx];
    float startY = BASE_Y - ((src.getSize() + 1) * DISK_HEIGHT);
    float targetX = ROD_X[destIdx];
    float targetY = BASE_Y - ((dest.getSize() + 1) * DISK_HEIGHT);
    float peakY = BASE_Y - ROD_HEIGHT - 30.f;

    sf::RectangleShape animatedDisk(sf::Vector2f(diskWidth, DISK_HEIGHT - 2.f));
    animatedDisk.setOrigin(diskWidth / 2.f, 0.f);
    animatedDisk.setFillColor(diskColors[(diskSize - 1) % 8]);
    animatedDisk.setOutlineThickness(1.f);
    animatedDisk.setOutlineColor(sf::Color::White);

    float currX = startX;
    float currY = startY;

    // Phase 1: Lift Up
    while (currY > peakY && window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
        }
        currY -= 6.f;
        animatedDisk.setPosition(currX, currY);

        renderScene(window, font);
        window.draw(animatedDisk);
        window.display();
        sf::sleep(sf::milliseconds(8));
    }

    // Phase 2: Slide Horizontally
    float stepX = (targetX > startX) ? 6.f : -6.f;
    while (abs(currX - targetX) > 5.f && window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
        }
        currX += stepX;
        animatedDisk.setPosition(currX, currY);

        renderScene(window, font);
        window.draw(animatedDisk);
        window.display();
        sf::sleep(sf::milliseconds(8));
    }
    currX = targetX;

    // Phase 3: Drop Down
    while (currY < targetY && window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
        }
        currY += 6.f;
        animatedDisk.setPosition(currX, currY);

        renderScene(window, font);
        window.draw(animatedDisk);
        window.display();
        sf::sleep(sf::milliseconds(8));
    }

    dest.push(diskSize);
    renderScene(window, font);
    sf::sleep(sf::milliseconds(150));
}

// Recursive Tower of Hanoi Solver
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
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tower of Hanoi - SFML Visualizer");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/calibri.ttf");
    }

    cout << "Enter number of disks for SFML animation (1 to 8, default 4): ";
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
                    currentActionText = "PUZZLE SOLVED IN " + to_string(stepCounter) + " MOVES!";
                }
            }
        }

        renderScene(window, font);
    }

    return 0;
}
