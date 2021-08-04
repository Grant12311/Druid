#include <Druid/gl_include.h>

#include <Druid/guard.h>
#include <Druid/vbo.h>

namespace Druid
{
    VBO::VBO()
    {
        glCall(glGenBuffers(1, &this->buffer));
    }

    VBO::VBO(const EarlyCreateType /*a_early*/) :
        buffer(0) {}

    VBO::VBO(VBO &&a_other)
    {
        this->buffer = a_other.buffer;
        a_other.buffer = 0;
    }

    VBO::~VBO()
    {
        glCall(glDeleteBuffers(1, &this->buffer));
    }

    void VBO::bind() const
    {
        glCall(glBindBuffer(GL_ARRAY_BUFFER, this->buffer));
    }

    void VBO::unbind() const
    {
        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void VBO::fill(const int a_size, const void* a_data, const unsigned int a_usage)
    {
        glCall(glBufferData(GL_ARRAY_BUFFER, a_size, a_data, a_usage));
    }

    VBO& VBO::operator=(VBO &&a_rhs)
    {
        if (this == &a_rhs)
            return *this;

        this->buffer = a_rhs.buffer;
        a_rhs.buffer = 0;

        return *this;
    }
}
