#ifndef DRUID_IBO_H
#define DRUID_IBO_H

namespace Druid
{
    class IBO
    {
    public:
        unsigned int buffer;

        void bind() const;
        void unbind() const;

        void fill(const int a_size, const void* a_data, const unsigned int a_usage);

        IBO();
        ~IBO();
    };
}

#endif
