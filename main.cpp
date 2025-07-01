#include "conway.hpp"

int main() {
    const int WIDTH = 80;
    const int HEIGHT = 24;
    const int GENERATIONS = 1000;
    
    Conway game(WIDTH, HEIGHT);
    game.run(GENERATIONS);
    
    return 0;
}