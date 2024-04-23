//
// Created by mateusz-krol on 4/23/24.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader(const std::string& fileName);

    void Bind();

    virtual ~Shader();
protected:
private:
    static const unsigned int NUM_SHADERS = 2;
    Shader(const Shader& other) {}
    void operator=(const Shader& other) {}

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
};


#endif //OPENGL_SHADER_H
