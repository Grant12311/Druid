#ifndef DRUID_BUFFERS_H
#define DRUID_BUFFERS_H

#include "guards.h"

namespace Druid
{
    struct VBO
    {
        unsigned int buffer;

        void bind() const
        {
            glCall(glBindBuffer(GL_ARRAY_BUFFER, this->buffer));
        }

        void unbind() const
        {
            glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        }

        void fill(const int a_size, const void* a_data, const unsigned int a_usage)
        {
            glCall(glBufferData(GL_ARRAY_BUFFER, a_size, a_data, a_usage));
        }

        VBO()
        {
            glCall(glGenBuffers(1, &this->buffer));
        }

        ~VBO()
        {
            glCall(glDeleteBuffers(1, &this->buffer));
        }
    };

    struct IBO
    {
        unsigned int buffer;

        void bind() const
        {
            glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer));
        }

        void unbind() const
        {
            glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }

        void fill(const int a_size, const void* a_data, const unsigned int a_usage)
        {
            glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_size, a_data, a_usage));
        }

        IBO()
        {
            glCall(glGenBuffers(1, &this->buffer));
        }

        ~IBO()
        {
            glCall(glDeleteBuffers(1, &this->buffer));
        }
    };

    struct VAO
    {
        unsigned int buffer;

        void bind() const
        {
            glCall(glBindVertexArray(this->buffer));
        }

        void unbind() const
        {
            glCall(glBindVertexArray(0));
        }

        void setAttrib(const int a_index, const int a_count, const int a_type, const bool a_normalized, const int a_stride, const int a_offset)
        {
            glCall(glVertexAttribPointer(a_index, a_count, a_type, a_normalized, a_stride, (void*)a_offset));
            glCall(glEnableVertexAttribArray(a_index));
        }

        VAO()
        {
            glCall(glGenVertexArrays(1, &this->buffer));
        }

        ~VAO()
        {
            glCall(glDeleteVertexArrays(1, &this->buffer));
        }
    };
}

#endif
