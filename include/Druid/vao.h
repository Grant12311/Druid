#ifndef DRUID_VAO_H
#define DRUID_VAO_H

namespace Druid
{
    class VAO
    {
    public:
        unsigned int buffer;

        void bind() const;
        void unbind() const;

        void setAttrib(const int a_index, const int a_count, const int a_type, const bool a_normalized, const int a_stride, const int a_offset);

        VAO();
        ~VAO();
    };
}

#endif
