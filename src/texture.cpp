#include <Druid/gl_include.h>

#include <Druid/texture.h>

namespace Druid
{
    void Texture2D::bind(const unsigned int a_slot) const
    {
        glCall(glActiveTexture(GL_TEXTURE0 + a_slot));
        glCall(glBindTexture(GL_TEXTURE_2D, this->m_ID));
    }

    void Texture2D::unbind() const
    {
        glCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    Texture2D::operator unsigned int() const
    {
        return this->m_ID;
    }

    Texture2D::Texture2D(const char* const a_path, const bool a_flipY, const unsigned int a_minFilter, const unsigned int a_magFilter, const unsigned int a_wrapS, const unsigned int a_wrapT) :
        m_path{a_path}, m_width{0}, m_height{0}, m_bpp{0}
    {
        stbi_set_flip_vertically_on_load(a_flipY);
        unsigned char* const imageData = stbi_load(a_path, &this->m_width, &this->m_height, &this->m_bpp, 4);

        glCall(glGenTextures(1, &this->m_ID));
        glCall(glBindTexture(GL_TEXTURE_2D, this->m_ID));

        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, a_minFilter));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, a_minFilter));

        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, a_wrapS));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, a_wrapT));

        glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_width, this->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData));

        if (imageData)
        {
            glCall(glGenerateMipmap(GL_TEXTURE_2D));
            stbi_image_free(imageData);
        }
        glCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    Texture2D::~Texture2D()
    {
        glCall(glDeleteTextures(1, &this->m_ID));
    }
}
