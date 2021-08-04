#include <iostream>

#include <Druid/gl_include.h>

#include <Druid/guard.h>
#include <Druid/ibo.h>

namespace Druid
{
    IBO::IBO(const EarlyCreateType /*a_early*/) :
        buffer(0) {}

    IBO::IBO()
    {
        glCall(glGenBuffers(1, &this->buffer));
    }

    IBO::IBO(IBO &&a_other)
    {
        this->buffer = a_other.buffer;
        a_other.buffer = 0;
    }

    IBO::~IBO()
    {
        glCall(glDeleteBuffers(1, &this->buffer));
    }

    void IBO::bind() const
    {
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer));
    }

    void IBO::unbind() const
    {
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void IBO::fill(const int a_size, const void* a_data, const unsigned int a_usage)
    {
        glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_size, a_data, a_usage));
    }

    IBO& IBO::operator=(IBO&& a_rhs)
    {
        if (this == &a_rhs)
            return *this;

        this->buffer = a_rhs.buffer;
        a_rhs.buffer = 0;

        return *this;
    }
}
