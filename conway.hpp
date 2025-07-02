#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <vector>
#include <chrono>
#include <utility>

class Conway {
public:
    Conway();
    void update();
    void render();
    void run();

private:
    int width;
    int height;
    std::vector<std::vector<bool>> grid;
    std::chrono::time_point<std::chrono::steady_clock> last_time;
    double fps = 0.0;
    
    std::pair<int, int> getTerminalSize() const;
    int countNeighbors(int x, int y) const;
    void initializeGrid();
    void resizeGrid();
};

#endif