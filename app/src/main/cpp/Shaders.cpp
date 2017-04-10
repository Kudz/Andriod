//
// Created by kamil7 on 2017-03-29.
//

#include "Shaders.h"

void DisplayGLError(const char* error_message)
{
    for (GLint error = glGetError(); error; error = glGetError())
    {
        __android_log_print(ANDROID_LOG_ERROR, LOG_SHADER_TAG, "after %s() glError (%d)\n", error_message, error);
    }
}

GLuint loadShader(GLenum shaderType, const char* text)
{
    // adding end of char chain sign on the end of file
    size_t textSize = strlen(text);
    char *glslSource = new char[textSize + 1];
    strcpy(glslSource, text);
    glslSource[textSize] = '\0';

    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        const char* glslSourceConst = glslSource;
        GLint iShaderLen = textSize;
        glShaderSource(shader, 1, &glslSourceConst, (GLint*)&iShaderLen);
//        glShaderSource(shader, 1, &text, NULL);
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
                    LOG_SHADER_E("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}