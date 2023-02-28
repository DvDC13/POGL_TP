#pragma once

#include <iostream>

namespace MyGL
{
    class Matrix4
    {
    public:
        Matrix4();

        void operator*=(const Matrix4& other);

        static Matrix4 Identity();

        friend std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix);

    private:
        double m_Matrix[4][4];
    };

    inline std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix)
    {
        stream << "Matrix4:" << std::endl;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                stream << matrix.m_Matrix[i][j] << " ";
            }
            stream << std::endl;
        }
        return stream;
    }
}