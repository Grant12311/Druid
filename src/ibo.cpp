#include "../include/gl_include.h"

#include "../include/guard.h"
#include "../include/ibo.h"

namespace Druid
{
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

    IBO::IBO()
    {
        glCall(glGenBuffers(1, &this->buffer));
    }

    IBO::~IBO()
    {
        glCall(glDeleteBuffers(1, &this->buffer));
    }
}
