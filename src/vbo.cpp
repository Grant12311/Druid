#include "../include/gl_include.h"

#include "../include/guard.h"
#include "../include/vbo.h"

namespace Druid
{
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

    VBO::VBO()
    {
        glCall(glGenBuffers(1, &this->buffer));
    }

    VBO::~VBO()
    {
        glCall(glDeleteBuffers(1, &this->buffer));
    }
}
