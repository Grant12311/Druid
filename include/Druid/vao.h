#ifndef DRUID_VAO_H
#define DRUID_VAO_H

#include <Druid/early_create.h>

namespace Druid
{
    class VAO
    {
    public:
        unsigned int buffer;

        VAO();
        VAO(const EarlyCreateType /*a_early*/);
        VAO(const VAO &a_other) = delete;
        VAO(VAO &&a_other);

        ~VAO();

        void bind() const;
        void unbind() const;

        void setAttrib(const int a_index, const int a_count, const int a_type, const bool a_normalized, const int a_stride, const int a_offset);

        VAO& operator=(const VAO &a_rhs) = delete;
        VAO& operator=(VAO &&a_rhs);
    };
}

#endif
