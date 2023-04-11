#pragma once

#include <string>
#include <GL/glew.h>

#include "stb_image.h"

#include "Error.h"

class Texture
{
public:
    Texture() = default;
    Texture(const std::string& path);

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    void destroy() const;

    inline int getRendererID() const { return m_RendererID; }
    inline const std::string& getFilepath() const { return m_Filepath; }
    inline unsigned char* getLocalBuffer() const { return m_LocalBuffer; }
    inline int getWidth() const { return m_Width; }
    inline int getHeight() const { return m_Height; }
    inline int getBPP() const { return m_BPP; }

private:
    unsigned int m_RendererID;
    std::string m_Filepath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
};