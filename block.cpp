//
// Created by mateusz-krol on 6/29/24.
//

#include "block.h"

Block::Block(Type type) : type_{type}  {}


void Block::rotateR() {
    switch(orientation_) {
        case NORTH:
            orientation_ = EAST;
            break;
        case WEST:
            orientation_ = NORTH;
            break;
        case SOUTH:
            orientation_ = WEST;
            break;
        case EAST:
            orientation_ = SOUTH;
            break;
    }
}

void Block::rotateL() {
    switch(orientation_) {
        case NORTH:
            orientation_ = WEST;
            break;
        case WEST:
            orientation_ = SOUTH;
            break;
        case SOUTH:
            orientation_ = EAST;
            break;
        case EAST:
            orientation_ = NORTH;
            break;
    }
}


