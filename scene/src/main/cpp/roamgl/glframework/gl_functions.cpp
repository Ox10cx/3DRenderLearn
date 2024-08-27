//
// Created by 龚喜 on 2024/8/23.
//

#include "gl_functions.h"
#include <GLES3/gl3.h>
#include "log.h"


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        Log::Error(Event::OpenGL, "[OpenGL Error] (\" %d \") %s %s : %d", error, function, file, line);
        return false;
    }
    return true;
}
