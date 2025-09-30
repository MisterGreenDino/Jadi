#pragma once
#include <string>
#include <glad/glad.h>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

private:
    GLuint programID;

    std::string LoadFile(const std::string& path);
    GLuint CompileShader(GLenum type, const std::string& source);
};
