//
// Created by mateusz-krol on 6/11/24.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture {
public:
    Texture(const std::string& fileName);

    void Bind();

    virtual ~Texture();
protected:
private:
    Texture(const Texture& other) {}
    void operator=(const Texture& other) {}

    GLuint m_texture;
};


#endif //OPENGL_TEXTURE_H
