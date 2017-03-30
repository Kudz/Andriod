//
// Created by kamil7 on 2017-03-28.
//

#include "TriangleShader.h"

TriangleShader::TriangleShader(std::string path)
{
    this->path = path;
    this->compileProgram();
}

TriangleShader::TriangleShader()
{
    this->compileProgram();
}

TriangleShader::TriangleShader(std::string vertexShader, std::string fragmentShader)
{
    this->compileProgram(vertexShader, fragmentShader);
}

void TriangleShader::compileProgram()
{
    this->ShaderIds[0] = glCreateProgram();
    LOG_TRIANGLE_SHADER_I("ERROR: Could not create the shader program");
    ///SOURCEFOLDERPATH is a macro including a path to a source folder; macro is defined in CMakeLists
    std::string sourceFolderPath = SOURCEFOLDERPATH;
//    this->ShaderIds[1] = LoadShader(sourceFolderPath+"/shaders/TriangleShader.fragment.glsl", GL_FRAGMENT_SHADER); ///TODO path is hardcoded not smart, use xml or others
//    this->ShaderIds[2] = LoadShader(sourceFolderPath+"/shaders/TriangleShader.vertex.glsl", GL_VERTEX_SHADER);
    std::size_t last_slash = sourceFolderPath.find_last_of("/");
    std::string result = sourceFolderPath.substr(0, last_slash);
    this->ShaderIds[1] = LoadShader(sourceFolderPath+"/res/raw/triangle_shader_fragment", GL_FRAGMENT_SHADER); ///TODO path is hardcoded not smart, use xml or others
    this->ShaderIds[2] = LoadShader(sourceFolderPath+"/res/raw/triangle_shader_vertex", GL_VERTEX_SHADER);
    glAttachShader(this->ShaderIds[0], this->ShaderIds[1]);
    glAttachShader(this->ShaderIds[0], this->ShaderIds[2]);
    glLinkProgram(this->ShaderIds[0]);
    LOG_TRIANGLE_SHADER_I("ERROR: Could not link the shader program");
}

GLuint TriangleShader::loadShader(GLenum shaderType, const char* pSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOG_TRIANGLE_SHADER_I("ERROR: Could not compile shader");
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

void TriangleShader::compileProgram(std::string vertexShader, std::string fragmentShader)
{
    this->ShaderIds[0] = glCreateProgram();
    DisplayGLError("ERROR: Could not create the shader program");
    this->ShaderIds[1] = loadShader(GL_FRAGMENT_SHADER, fragmentShader.c_str());
    this->ShaderIds[2] = loadShader(GL_VERTEX_SHADER, vertexShader.c_str());
    glAttachShader(this->ShaderIds[0], this->ShaderIds[1]);
    glAttachShader(this->ShaderIds[0], this->ShaderIds[2]);
    glLinkProgram(this->ShaderIds[0]);
    DisplayGLError("ERROR: Could not link the shader program");
}

GLuint TriangleShader::getProgramID(int part)
{
    return this->ShaderIds[part];
}

TriangleShader::~TriangleShader()
{
    glDetachShader(this->ShaderIds[0], this->ShaderIds[1]);
    glDetachShader(this->ShaderIds[0], this->ShaderIds[2]);
    glDeleteShader(this->ShaderIds[1]);
    glDeleteShader(this->ShaderIds[2]);
    glDeleteProgram(this->ShaderIds[0]);
    DisplayGLError("ERROR: Could not destroy the shaders");
}
