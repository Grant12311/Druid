#ifndef DRUID_GUARD_H
#define DRUID_GUARD_H

#ifndef DRUID_DISABLE_GLCALL
    #define glCall(x) Druid::glClearErrors(); x; if (!(Druid::glLogError(#x, __FILE__, __LINE__))) __builtin_trap();
#else
    #define glCall(x) x;
#endif // DRUID_DISABLE_GLCALL

namespace Druid
{
    void glClearErrors();
    bool glLogError(const char* a_functionName, const char* a_fileName, const int a_line);
}

#endif
