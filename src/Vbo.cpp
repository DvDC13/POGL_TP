#include "Vbo.h"

namespace MyGL
{
    Vbo::Vbo()
    {
        glGenBuffers(1, &m_VboID);
    }

    void Vbo::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
    }

    void Vbo::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Vbo::setData(const void* data, unsigned int size, unsigned int usage)
    {
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        unbind();
    }

    void Vbo::destroy()
    {
        glDeleteBuffers(1, &m_VboID);
    }
}