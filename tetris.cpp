//
// Created by mateusz-krol on 6/19/24.
//

#include "tetris.h"

Tetris::Tetris() {
    srand (time(NULL));
    currentBlock = Block(rand() % 7);
    nextBlock = Block(rand() % 7);

    for(int i=-5;i<5;i++) {
        for(int j=-9; j<11;j++) {
            field[{i, j}] = false;
        }
    }
}


void Tetris::play(Display& display) {
    Shader shader("../res/basicShader");
    Texture texture("../res/imgs/red.jpg");

    SDL_Event event;
    bool isRunning = true;

    Vertex* bottomVertices;
    int bottomCount = 0;

    std::clock_t start, now;
    start = std::clock();
    double ticks = 0;
    double time_passed;

    while(isRunning) {
        for(int i=-5;i<5;i++) {
            if(field[{i, 10}]) {
                hasLost = true;
                isRunning = false;
            }
        }
        display.Clear(0.0f, 0.25f, 0.3f, 1.0f);

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    inputReact(event.key.keysym.sym);
                    break;

                default:
                    break;
            }
        }

        if(positionY == -8 ||
                field[{positionX+1, positionY}]  ||
                field[{positionX, positionY}]) {

            field[{positionX+1, positionY+2}] = true;
            field[{positionX, positionY+2}] = true;
            field[{positionX+1, positionY+1}] = true;
            field[{positionX, positionY+1}] = true;



            bottomVertices = bottomVerticesRepresentation(bottomVertices, bottomCount, positionX, positionY);
            bottomCount+=1;

            currentBlock = Block(rand() % 7);
            positionY = 10;
            positionX = 0;
        }

        now = std::clock();
        time_passed = 100 * (now - start) / (double) CLOCKS_PER_SEC;
        if(time_passed > ticks+1) {
            if(positionY>-8) positionY-=1;
            ticks++;
        }

        auto currentVertices = currentBlockRepresentation();

        Mesh currentMesh(currentVertices, 24);

        shader.Bind();
        texture.Bind();
        currentMesh.Draw();
        if(bottomCount>0) {
            Mesh bottomMesh(bottomVertices, bottomCount*24);
            bottomMesh.Draw();
        }

        display.Update();
    }

    if(hasLost) printf("Game over!\n");
}

void Tetris::inputReact(int input) {
    switch(input) {
        case SDLK_UP:
            while(positionY > -8 &&
            !field[{positionX, positionY}] &&
            !field[{positionX+1, positionY}]) positionY-=1;
            break;
        case SDLK_DOWN:
            if(positionY > -8) positionY-=1;
            break;
        case SDLK_RIGHT:
            if(positionX<3) positionX+=1;
            break;
        case SDLK_LEFT:
            if(positionX>-5) positionX-=1;
            break;
        case SDLK_g:
            switch(orientation) {
                case NORTH:
                    orientation = EAST;
                    break;
                case EAST:
                    orientation = SOUTH;
                    break;
                case SOUTH:
                    orientation = WEST;
                    break;
                case WEST:
                    orientation = NORTH;
                    break;
            }
            break;
        case SDLK_f:
            switch(orientation) {
                case NORTH:
                    orientation = WEST;
                    break;
                case WEST:
                    orientation = SOUTH;
                    break;
                case SOUTH:
                    orientation = EAST;
                    break;
                case EAST:
                    orientation = NORTH;
                    break;
            }
            break;
        default:
            break;
    }
}

Vertex* Tetris::currentBlockRepresentation() {
    float c2 = 0.00125f;
    float c1 = 0.00167f;
    float size_ = 40;
    Vertex v[] = {
            // First block
            Vertex(glm::vec3((float)positionX/10, (float)positionY/10, 0.0),
                   glm::vec2(0.0, 1.0)),
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10, 0.0),
                   glm::vec2(1.0, -1.0)),
            Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(-1.0, -1.0)),

            Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(0.0, 1.0)),
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10, 0.0),
                   glm::vec2(1.0, -1.0)),
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(-1.0, -1.0)),
            // Second block
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10, 0.0),
                   glm::vec2(0.0, 1.0)),
            Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10, 0.0),
                   glm::vec2(1.0, -1.0)),
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(-1.0, -1.0)),

            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(0.0, 1.0)),
            Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10, 0.0),
                   glm::vec2(1.0, -1.0)),
            Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(-1.0, -1.0)),

            // Third block
            Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(0.0, 1.0)),
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(1.0, -1.0)),
            Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 2*0.1, 0.0),
                   glm::vec2(-1.0, -1.0)),

            Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 2*0.1, 0.0),
                   glm::vec2(0.0, 1.0)),
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(1.0, -1.0)),
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 2*0.1, 0.0),
                   glm::vec2(-1.0, -1.0)),

            // Fourth block
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(0.0, 1.0)),
            Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(1.0, -1.0)),
            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 2*0.1, 0.0),
                   glm::vec2(-1.0, -1.0)),

            Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 2*0.1, 0.0),
                   glm::vec2(0.0, 1.0)),
            Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10 - 0.1, 0.0),
                   glm::vec2(1.0, -1.0)),
            Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10 - 2*0.1, 0.0),
                   glm::vec2(-1.0, -1.0)),
    };
    auto ptr = (Vertex*) malloc(sizeof(v));
    memcpy(ptr, v, sizeof(v));
    return ptr;
}

Vertex* Tetris::bottomVerticesRepresentation(Vertex* bottomVertices, int bottomSize, int positionX, int positionY) {
    float c2 = 0.00125f;
    float c1 = 0.00167f;
    float size_ = 40;
    auto newSize = 24 * bottomSize + 24;
    auto ptr = (Vertex*) malloc(newSize * sizeof(Vertex));

    if (bottomVertices != nullptr) {
        memcpy(ptr, bottomVertices, 24 * bottomSize * sizeof(Vertex));
    }

    // First block
    bottomSize*=24;
    ptr[bottomSize] = Vertex(glm::vec3((float)positionX/10, (float)positionY/10, 0.0),
           glm::vec2(0.0, 1.0));
    ptr[bottomSize+1] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10, 0.0),
                   glm::vec2(1.0, -1.0));
    ptr[bottomSize+2] = Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(-1.0, -1.0));

    ptr[bottomSize+3] = Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(0.0, 1.0));
    ptr[bottomSize+4] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10, 0.0),
           glm::vec2(1.0, -1.0));
    ptr[bottomSize+5] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(-1.0, -1.0));
    // Second block
    ptr[bottomSize+6] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10, 0.0),
           glm::vec2(0.0, 1.0));
    ptr[bottomSize+7] = Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10, 0.0),
           glm::vec2(1.0, -1.0));
    ptr[bottomSize+8] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(-1.0, -1.0));

    ptr[bottomSize+9] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(0.0, 1.0));
    ptr[bottomSize+10] = Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10, 0.0),
           glm::vec2(1.0, -1.0));
    ptr[bottomSize+11] = Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(-1.0, -1.0));

    // Third block
    ptr[bottomSize+12] = Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(0.0, 1.0));
    ptr[bottomSize+13] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(1.0, -1.0));
    ptr[bottomSize+14] = Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 2*0.1, 0.0),
           glm::vec2(-1.0, -1.0));

    ptr[bottomSize+15] = Vertex(glm::vec3((float)positionX/10, (float)positionY/10 - 2*0.1, 0.0),
           glm::vec2(0.0, 1.0));
    ptr[bottomSize+16] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(1.0, -1.0));
    ptr[bottomSize+17] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 2*0.1, 0.0),
           glm::vec2(-1.0, -1.0));

    // Fourth block
    ptr[bottomSize+18] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(0.0, 1.0));
    ptr[bottomSize+19] = Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(1.0, -1.0));
    ptr[bottomSize+20] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 2*0.1, 0.0),
           glm::vec2(-1.0, -1.0));

    ptr[bottomSize+21] = Vertex(glm::vec3((float)positionX/10 + 0.1, (float)positionY/10 - 2*0.1, 0.0),
           glm::vec2(0.0, 1.0));
    ptr[bottomSize+22] = Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10 - 0.1, 0.0),
           glm::vec2(1.0, -1.0));
    ptr[bottomSize+23] = Vertex(glm::vec3((float)positionX/10 + 2*0.1, (float)positionY/10 - 2*0.1, 0.0),
           glm::vec2(-1.0, -1.0));

    return ptr;
}
