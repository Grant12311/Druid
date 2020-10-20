#include <Druid/gl_include.h>

#include <Druid/guard.h>
#include <Druid/vao.h>

namespace Druid
{
    void VAO::bind() const
    {
        glCall(glBindVertexArray(this->buffer));
    }

    void VAO::unbind() const
    {
        glCall(glBindVertexArray(0));
    }

    void VAO::setAttrib(const int a_index, const int a_count, const int a_type, const bool a_normalized, const int a_stride, const int a_offset)
    {
        glCall(glVertexAttribPointer(a_index, a_count, a_type, a_normalized, a_stride, (void*)a_offset));
        glCall(glEnableVertexAttribArray(a_index));
    }

    VAO::VAO()
    {
        glCall(glGenVertexArrays(1, &this->buffer));
    }

    VAO::~VAO()
    {
        glCall(glDeleteVertexArrays(1, &this->buffer));
    }
}
