#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <vector>
#include <utility>

class Conway {
public:
    Conway();
    void update();
    void render() const;
    void run();

private:
    int width;
    int height;
    std::vector<std::vector<bool>> grid;
    
    std::pair<int, int> getTerminalSize() const;
    int countNeighbors(int x, int y) const;
    void initializeGrid();
    void resizeGrid();
};

#endif