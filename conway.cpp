#include "conway.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string>
#include <cstdio>

Conway::Conway() : last_time(std::chrono::steady_clock::now()) {
    std::srand(std::time(nullptr));
    resizeGrid();
}

std::pair<int, int> Conway::getTerminalSize() const {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return std::make_pair(size.ws_col, size.ws_row - 1);
}

void Conway::resizeGrid() {
    auto dimensions = getTerminalSize();
    int newWidth = dimensions.first;
    int newHeight = dimensions.second;
    
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

void Conway::render() {
    auto now = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double>(now - last_time).count();
    fps = 0.9 * fps + 0.1 * (1.0 / elapsed);
    last_time = now;

    std::string buffer;
    buffer.reserve((width + 1) * height + 100);
    
    buffer.append("\033[H");
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            buffer += grid[y][x] ? '0' : ' ';
        }
        buffer += '\n';
    }

    char fps_str[20];
    snprintf(fps_str, sizeof(fps_str), "%.1f", fps);

    buffer += "Update: Buffer approach ";
    buffer += "| Ctrl+C to quit ";
    buffer += "| FPS: ";
    buffer += fps_str;
    
    std::cout << buffer << std::flush;
}

void Conway::run() {
    while (true) {
        resizeGrid();
        render();
        update();
        usleep(100000);
    }
}