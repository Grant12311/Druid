#ifndef DRUID_TEXTURE_H
#define DRUID_TEXTURE_H

#include "gl_include.h"

#include <stb/stb_image.h>

#include "guard.h"

namespace Druid
{
    class Texture2D
    {
    private:
        unsigned int m_ID;
        const char* m_path;
        int m_width;
        int m_height;
        int m_bpp;
    public:
        void bind(const unsigned int a_slot = 0) const;
        void unbind() const;

        inline int getWidth() const {return this->m_width;}
        inline int getHeight() const {return this->m_height;}

        operator unsigned int() const;

        Texture2D(const char* const a_path, const bool a_flipY = true, const unsigned int a_minFilter = GL_LINEAR, const unsigned int a_magFilter = GL_LINEAR, const unsigned int a_wrapS = GL_CLAMP_TO_EDGE, const unsigned int a_wrapT = GL_CLAMP_TO_EDGE);
        ~Texture2D();
    };
};

#endif
