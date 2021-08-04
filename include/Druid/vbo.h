#ifndef DRUID_VBO_H
#define DRUID_VBO_H

#include <Druid/early_create.h>

namespace Druid
{
    class VBO
    {
    public:
        unsigned int buffer;

        VBO();
        VBO(const EarlyCreateType /*a_early*/);
        VBO(const VBO &a_other) = delete;
        VBO(VBO &&a_other);

        ~VBO();

        void bind() const;
        void unbind() const;

        void fill(const int a_size, const void* a_data, const unsigned int a_usage);

        VBO& operator=(const VBO &a_rhs) = delete;
        VBO& operator=(VBO &&a_rhs);
    };
}

#endif
