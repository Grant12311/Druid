#ifndef DRUID_TEXTURE_H
#define DRUID_TEXTURE_H

#include <stb/stb_image.h>

namespace Druid
{
    class Texture
    {
    private:
        unsigned int m_ID;
        const char* m_path;
        int m_width;
        int m_height;
        int m_bpp;
    public:
        void bind(const unsigned int a_slot = 0) const
        {
            glCall(glActiveTexture(GL_TEXTURE0 + a_slot));
            glCall(glBindTexture(GL_TEXTURE_2D, this->m_ID));
        }

        void unbind() const
        {
            glCall(glBindTexture(GL_TEXTURE_2D, 0));
        }

        inline int getWidth() const {return this->m_width;}
        inline int getHeight() const {return this->m_height;}

        Texture(const char* const a_path, const bool a_flipY = true, const unsigned int a_minFilter = GL_LINEAR, const unsigned int a_magFilter = GL_LINEAR, const unsigned int a_wrapS = GL_CLAMP_TO_EDGE, const unsigned int a_wrapT = GL_CLAMP_TO_EDGE) :
            m_path{a_path}, m_width{0}, m_height{0}, m_bpp{0}
        {
            stbi_set_flip_vertically_on_load(a_flipY);
            unsigned char* const imageData = stbi_load(a_path, &this->m_width, &this->m_height, &this->m_bpp, 4);

            glCall(glGenTextures(1, &this->m_ID));
            glCall(glBindTexture(GL_TEXTURE_2D, this->m_ID));

            glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, a_minFilter));
            glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, a_minFilter));

            glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, a_minFilter));
            glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, a_minFilter));

            glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_width, this->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData));
            glCall(glBindTexture(GL_TEXTURE_2D, 0));

            if (imageData)
            {
                stbi_image_free(imageData);
            }
        }

        ~Texture()
        {
            glCall(glDeleteTextures(1, &this->m_ID));
        }
    };
};

#endif
