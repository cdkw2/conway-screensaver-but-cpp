#include "conway.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/ioctl.h>
#include <unistd.h>

Conway::Conway() {
    std::srand(std::time(nullptr));
    resizeGrid();
}

std::pair<int, int> Conway::getTerminalSize() const {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return {size.ws_col, size.ws_row - 1};
}

void Conway::resizeGrid() {
    auto [newWidth, newHeight] = getTerminalSize();
    
    if (newWidth != width || newHeight != height) {
        width = newWidth;
        height = newHeight;
        grid.resize(height);
        for (auto& row : grid) {
            row.resize(width);
        }
        initializeGrid();
    }
}

void Conway::initializeGrid() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x] = std::rand() % 2;
        }
    }
}

int Conway::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            
            int nx = (x + dx + width) % width;
            int ny = (y + dy + height) % height;
            
            if (grid[ny][nx]) {
                ++count;
            }
        }
    }
    return count;
}

void Conway::update() {
    auto newGrid = grid;
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int neighbors = countNeighbors(x, y);
            
            if (grid[y][x]) {
                newGrid[y][x] = (neighbors == 2 || neighbors == 3);
            } else {
                newGrid[y][x] = (neighbors == 3);
            }
        }
    }
    
    grid = newGrid;
}

void Conway::render() const {
    std::cout << "\033[2J\033[H";
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << (grid[y][x] ? "0" : " ");
        }
        std::cout << "\n";
    }
    std::cout << "Rezise to change grid size | Ctrl+C to quit" << std::flush;
}

void Conway::run() {
    while (true) {
        resizeGrid();
        render();
        update();
        usleep(100000);
    }
}