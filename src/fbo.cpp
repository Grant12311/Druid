#include <cstdlib>

#include <Druid/gl_include.h>

#include <Druid/fbo.h>

namespace Druid
{
    void FBO::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->buffer);
    }

    void FBO::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    FBO::FBO(const unsigned int a_width, const unsigned int a_height)
    {
        glGenFramebuffers(1, &this->buffer);
        glBindFramebuffer(GL_FRAMEBUFFER, this->buffer);

        glGenTextures(2, &this->colorAttachment);

        glBindTexture(GL_TEXTURE_2D, this->colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, a_width, a_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorAttachment, 0);

        glBindTexture(GL_TEXTURE_2D, this->depthAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, a_width, a_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->depthAttachment, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            exit(1);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    FBO::~FBO()
    {
        glDeleteTextures(2, &this->colorAttachment);
        glDeleteFramebuffers(1, &this->buffer);
    }
}
