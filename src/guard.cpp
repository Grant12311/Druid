#include <iostream>

#include <Druid/gl_include.h>

namespace Druid
{
    void glClearErrors()
    {
         while (glGetError() != GL_NO_ERROR);
    }

    bool glLogError(const char* a_functionName, const char* a_fileName, const int a_line)
    {
        while (unsigned int error = glGetError())
        {
            std::cerr << "[OpenGL Error] {" << error << "}\ncaused by " << a_functionName << "\non line number " << a_line << "\nin " << a_fileName << std::endl;
            return false;
        }

        return true;
    }
}
