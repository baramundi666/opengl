//
// Created by mateusz-krol on 6/19/24.
//

#ifndef OPENGL_TETRIS_H
#define OPENGL_TETRIS_H

#include <iostream>
#include <random>
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
#include "block.h"

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

    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> rand_;


    std::map<std::pair<int, int>, bool> field;
    std::atomic<bool> isRunning{true};
    std::mutex mutex_;
    Vertex* bottomVertices;
    Vertex* currentVertices;
    int bottomCount = 0;
    Block currentBlock = Block(O);
    Block nextBlock = Block(O);
    int width = 10;
    int height = 20;
    int positionY = height/2;
    int positionX = 0;
    Display* display_;
};


#endif //OPENGL_TETRIS_H
