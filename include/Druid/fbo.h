#ifndef DRUID_FBO_H
#define DRUID_FBO_H

namespace Druid
{
    class FBO
    {
    public:
        unsigned int buffer;
        unsigned int colorAttachment, depthAttachment;

        void bind();
        void unbind();

        FBO(const unsigned int a_width, const unsigned int a_height);
        ~FBO();
    };
}

#endif
