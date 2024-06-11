//
// Created by mateusz-krol on 6/11/24.
//

#ifndef OPENGL_MESH_H
#define OPENGL_MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex {
public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord) {
        this->pos = pos;
        this->texCoord = texCoord;
    }

    inline glm::vec3* getPos() {return &pos;}
    inline glm::vec2* getTexCoord() {return &texCoord;}
protected:
private:
    glm::vec3 pos;
    glm::vec2 texCoord;
};

enum {
    POSITION_VB,
    TEXCOORD_VB
};

class Mesh {
public:
    Mesh(Vertex* vertices, unsigned int numVertices);

    void Draw();

    virtual ~Mesh();
protected:
private:
    static const unsigned int NUM_BUFFERS = 2;
    Mesh(const Mesh& other) {}
    void operator=(const Mesh& other) {}

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};


#endif //OPENGL_MESH_H
