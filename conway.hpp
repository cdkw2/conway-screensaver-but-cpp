#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <vector>

class Conway {
public:
    Conway(int width, int height);
    void update();
    void render() const;
    void run(int generations);

private:
    int width;
    int height;
    std::vector<std::vector<bool>> grid;
    
    int countNeighbors(int x, int y) const;
    void initializeGrid();
};

#endif