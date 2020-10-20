#ifndef DRUID_VBO_H
#define DRUID_VBO_H

namespace Druid
{
    class VBO
    {
    public:
        unsigned int buffer;

        void bind() const;
        void unbind() const;

        void fill(const int a_size, const void* a_data, const unsigned int a_usage);

        VBO();
        ~VBO();
    };
}

#endif
