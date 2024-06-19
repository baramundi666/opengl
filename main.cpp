#include <iostream>
#include "display.h"
#include "tetris.h"

int main() {
    Display display(600, 800, "Tetris");

    Tetris tetris;
    tetris.play(display);

    return 0;
}
