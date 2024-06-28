//
// Created by mateusz-krol on 6/19/24.
//

#ifndef OPENGL_TETRIS_H
#define OPENGL_TETRIS_H

#include <iostream>
#include <ctime>
#include <array>
#include <unistd.h>
#include <map>
#include <atomic>
#include <mutex>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

enum Block {
    I = 0,
    J = 1,
    L = 2,
    O = 3,
    S = 4,
    T = 5,
    Z = 6
};

enum Orientation {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};



class Tetris {
public:
    Tetris();

    void play();
protected:
private:
    void handleGraphics();
    void handleLogic();
    void handleInput();
    void handleKeyDown(int input);
    Vertex* currentBlockRepresentation();
    Vertex* bottomVerticesRepresentation(Vertex* bottomVertices, int bottomSize, int positionX, int positionY);

    Tetris(const Tetris& other) {}
    void operator=(const Tetris& other) {}


    std::map<std::pair<int, int>, bool> field;
    std::atomic<bool> isRunning{true};
    std::mutex mutex_;
    Vertex* bottomVertices;
    int bottomCount = 0;
    Block currentBlock;
    Block nextBlock;
    int positionY = 10;
    int positionX = 0;
    Orientation orientation = NORTH;
    Display* display_;
};


#endif //OPENGL_TETRIS_H
