//
// Created by kamil7 on 2017-03-29.
//

#include "Shaders.h"

GLuint LoadShader(std::string filename, GLenum shader_type)
{
    GLuint shader_id = 0;
    FILE* file;
    long file_size = -1;
    char* glsl_source;
    if (NULL != (file = fopen(filename.c_str(), "rb")) &&
        0 == fseek(file, 0, SEEK_END) &&
        -1 != (file_size = ftell(file)))
    {
        rewind(file);
        if (NULL != (glsl_source = (char*)malloc(file_size + 1)))
        {
            if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file))
            {
                glsl_source[file_size] = '\0';
                if (0 != (shader_id = glCreateShader(shader_type)))
                {
                    const char* glsl_source_const = glsl_source;
                    glShaderSource(shader_id, 1, &glsl_source_const, NULL);
                    glCompileShader(shader_id);
                    LOG_SHADER_E("Could not compile a shader");
                }
                else
                {
                    LOG_SHADER_I("Could not create a shader");
                }
            }
            else
            {
                LOG_SHADER_I("Could not read file");
            }
            free(glsl_source);
        }
        else
        {
            LOG_SHADER_I(" Could not allocate %li bytes.\n", file_size);
        }
        fclose(file);
    }
    else
    {
        if (NULL != file)
        {
            fclose(file);
        }
        LOG_SHADER_I(" Could not open file %s\n", filename.c_str());
    }
    return shader_id;
}

void DisplayGLError(const char* error_message)
{
    for (GLint error = glGetError(); error; error = glGetError())
    {
        LOG_SHADER_I("after %s() glError (0x%x)\n", error_message, error);
    }
}