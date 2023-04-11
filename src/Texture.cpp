#include "Texture.h"

Texture::Texture(const std::string& path)
    : m_Filepath(path), m_RendererID(0), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    if (m_LocalBuffer == nullptr)
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return;
    }

    glGenTextures(1, &m_RendererID); CHECK_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, m_RendererID); CHECK_GL_ERROR();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CHECK_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECK_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); CHECK_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); CHECK_GL_ERROR();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer); CHECK_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, 0); CHECK_GL_ERROR();

    if (m_LocalBuffer)
    {
        stbi_image_free(m_LocalBuffer);
    }
}

void Texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot); CHECK_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, m_RendererID); CHECK_GL_ERROR();
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0); CHECK_GL_ERROR();
}

void Texture::destroy() const
{
    glDeleteTextures(1, &m_RendererID); CHECK_GL_ERROR();
}