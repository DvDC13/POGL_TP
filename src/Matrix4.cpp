#include "Matrix4.h"

namespace MyGL
{
    Matrix4::Matrix4()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_Matrix[i][j] = 0;
            }
        }
    }

    void Matrix4::operator*=(const Matrix4& other)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float sum = 0;
                for (int k = 0; k < 4; k++)
                {
                    sum += m_Matrix[i][k] * other.m_Matrix[k][j];
                }
                m_Matrix[i][j] = sum;
            }
        }
    }

    Matrix4 Matrix4::Identity()
    {
        Matrix4 matrix;
        for (int i = 0; i < 4; i++) matrix.m_Matrix[i][i] = 1;
        return matrix;
    }

    float *Matrix4::get_pointer() const
    {
        return (float*)m_Matrix;
    }
}