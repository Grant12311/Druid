#ifndef DRUID_GUARDS_H
#define DRUID_GUARDS_H

#define ASSERT(x) if (!(x)) __builtin_trap()

#ifndef DRUID_DISABLE_GLCALL
    #define glCall(x) Druid::glClearErrors(); x; ASSERT(Druid::glLogError(#x, __FILE__, __LINE__));
#else
    #define glCall(x) x;
#endif // DRUID_DISABLE_GLCALL

#include <iostream>

namespace Druid
{
    static void glClearErrors()
    {
         while (glGetError() != GL_NO_ERROR);
    }

    static bool glLogError(const char* a_functionName, const char* a_fileName, const int a_line)
    {
        while (unsigned int error = glGetError())
        {
            std::cerr << "[OpenGL Error] {" << error << "}\ncaused by " << a_functionName << "\non line number " << a_line << "\nin " << a_fileName << std::endl;
            return false;
        }

        return true;
    }
}

#endif
