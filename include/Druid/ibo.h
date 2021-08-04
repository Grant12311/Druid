#ifndef DRUID_IBO_H
#define DRUID_IBO_H

#include <Druid/early_create.h>

namespace Druid
{
    class IBO
    {
    public:
        unsigned int buffer;

        IBO();
        IBO(const EarlyCreateType /*a_early*/);
        IBO(const IBO &a_other) = delete;
        IBO(IBO &&a_other);

        ~IBO();

        void bind() const;
        void unbind() const;

        void fill(const int a_size, const void* a_data, const unsigned int a_usage);

        IBO& operator=(const IBO &a_rhs) = delete;
        IBO& operator=(IBO&& a_rhs);
    };
}

#endif
