//
// Created by mateusz-krol on 6/29/24.
//

#ifndef OPENGL_BLOCK_H
#define OPENGL_BLOCK_H

enum Type {
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


class Block {
public:
    explicit Block(Type type);

    void rotateR();
    void rotateL();
private:
    Type type_;
    Orientation orientation_ = NORTH;
};


#endif //OPENGL_BLOCK_H
