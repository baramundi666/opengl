//
// Created by mateusz-krol on 6/19/24.
//

#include <thread>
#include "tetris.h"

void Tetris::handleGraphics() {
    Display display(600, 800, "Tetris");
    display_ = &display;
    Shader shader("../res/basicShader");
    Texture texture("../res/imgs/red.jpg");


    while(!isRunning);

    while(isRunning) {

        display_->Clear(0.0f, 0.25f, 0.3f, 1.0f);

        Mesh currentMesh(currentVertices, 24);

        shader.Bind();
        texture.Bind();
        currentMesh.Draw();
        if(bottomCount>0) {
            Mesh bottomMesh(bottomVertices, bottomCount*24);
            bottomMesh.Draw();
        }

        display_->Update();
    }
}

void Tetris::handleLogic() {
    std::clock_t start, now;
    start = std::clock();
    double ticks = 0;
    double time_passed;

    while(!isRunning);

    while(isRunning) {

        for(int i=-width/2;i<width/2;i++) {
            if(field[{i, height/2}]) {
                isRunning = false;
            }
        }


        handleInput();

        currentVertices = currentBlockRepresentation();


        if(positionY == -height/2 + 2 ||
           field[{positionX+1, positionY}]  ||
           field[{positionX, positionY}]) {

            field[{positionX+1, positionY+2}] = true;
            field[{positionX, positionY+2}] = true;
            field[{positionX+1, positionY+1}] = true;
            field[{positionX, positionY+1}] = true;

            bottomVertices = bottomVerticesRepresentation(bottomVertices, bottomCount, positionX, positionY);
            bottomCount+=1;

            currentBlock = nextBlock;
            nextBlock = Block(static_cast<Type>(rand_(mt)));
            positionY = 10;
            positionX = 0;
        }

        now = std::clock();
        time_passed = (now - start) / (double) CLOCKS_PER_SEC;
        if(time_passed > ticks+1) {
            if(positionY > -height/2 + 2) positionY-=1;
            ticks++;
        }

    }
}

Tetris::Tetris() : rd{}, mt{rd()}, rand_{0, 6} {

    currentBlock = Block(static_cast<Type>(rand_(mt)));
    nextBlock = Block(static_cast<Type>(rand_(mt)));


    for(int i=-width/2;i<width/2;i++) {
        for(int j=-height/2 + 1; j<height/2 + 1;j++) {
            field[{i, j}] = false;
        }
    }
}


void Tetris::play() {
    std::thread graphicsThread(&Tetris::handleGraphics, this);
    std::thread logicThread(&Tetris::handleLogic, this);
    graphicsThread.join();
    logicThread.join();
}

void Tetris::handleInput() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                handleKeyDown(event.key.keysym.sym);
                break;

            default:
                break;
        }
    }
}

void Tetris::handleKeyDown(int input) {
    switch(input) {
        case SDLK_UP:
            while(positionY > -height/2 + 2 &&
            !field[{positionX, positionY}] &&
            !field[{positionX+1, positionY}]) positionY-=1;
            break;
        case SDLK_DOWN:
            if(positionY > -height/2 + 2) positionY-=1;
            break;
        case SDLK_RIGHT:
            if(positionX < width/2 - 1) positionX+=1;
            break;
        case SDLK_LEFT:
            if(positionX > -width/2) positionX-=1;
            break;
        case SDLK_g:
            currentBlock.rotateR();
            break;
        case SDLK_f:
            currentBlock.rotateL();
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
