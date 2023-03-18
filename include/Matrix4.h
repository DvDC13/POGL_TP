#pragma once

#include <iostream>

#include <cmath>
#include <vector>

namespace MyGL
{
    class Matrix4
    {
    public:
        Matrix4();

        void operator*=(const Matrix4& other);

        static Matrix4 Identity();

        float *get_pointer() const;

        friend std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix);
        friend void frustum(Matrix4& matrix, const float &left, const float &right, const float &bottom, const float &top, const float &z_near, const float &z_far);
        friend void look_at(Matrix4& matrix, const float &eyeX, const float &eyeY, const float &eyeZ, const float &centerX, const float &centerY, const float &centerZ,
                float upX, float upY, float upZ);

    private:
        float m_Matrix[4][4];
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

    inline void frustum(Matrix4& matrix, const float &left, const float &right, const float &bottom, const float &top, const float &z_near, const float &z_far)
    {
        matrix.m_Matrix[0][0] = (2 * z_near) / (right - left);
        matrix.m_Matrix[0][2] = (right + left) / (right - left);

        matrix.m_Matrix[1][1] = (2 * z_near) / (top - bottom);
        matrix.m_Matrix[1][2] = (top + bottom) / (top - bottom);

        matrix.m_Matrix[2][2] = -(z_far + z_near) / (z_far - z_near);
        matrix.m_Matrix[2][3] = -(2 * z_far * z_near) / (z_far - z_near);

        matrix.m_Matrix[3][2] = -1;   
    }

    inline static std::vector<float> cross_product(const std::vector<float> &a, const std::vector<float> &b)
    {
        std::vector<float> result;
        result.push_back(a[1] * b[2] - a[2] * b[1]);
        result.push_back(a[2] * b[0] - a[0] * b[2]);
        result.push_back(a[0] * b[1] - a[1] * b[0]);
        return result;
    }

    inline static void normalize(std::vector<float> &a)
    {
        float sum = 0;
        for (int i = 0; i < a.size(); i++) sum += a[i] * a[i];
        float length = sqrt(sum);
        for (int i = 0; i < a.size(); i++) a[i] /= length;
    }

    inline void look_at(Matrix4& matrix, const float &eyeX, const float &eyeY, const float &eyeZ, const float &centerX, const float &centerY, const float &centerZ,
            float upX, float upY, float upZ)
    {
        Matrix4 matrix2;

        std::vector<float> look_direction;
        look_direction.push_back(centerX - eyeX);
        look_direction.push_back(centerY - eyeY);
        look_direction.push_back(centerZ - eyeZ);
        normalize(look_direction);

        std::vector<float> up;
        up.push_back(upX);
        up.push_back(upY);
        up.push_back(upZ);
        normalize(up);

        std::vector<float> right = cross_product(look_direction, up);
        normalize(right);

        up = cross_product(right, look_direction);
        normalize(up);

        matrix2.m_Matrix[0][0] = right[0];
        matrix2.m_Matrix[1][0] = right[1];
        matrix2.m_Matrix[2][0] = right[2];

        matrix2.m_Matrix[0][1] = up[0];
        matrix2.m_Matrix[1][1] = up[1];
        matrix2.m_Matrix[2][1] = up[2];

        matrix2.m_Matrix[0][2] = -look_direction[0];
        matrix2.m_Matrix[1][2] = -look_direction[1];
        matrix2.m_Matrix[2][2] = -look_direction[2];

        matrix2.m_Matrix[3][3] = 1;

        matrix *= matrix2;

        matrix.m_Matrix[3][0] = -eyeX;
        matrix.m_Matrix[3][1] = -eyeY;
        matrix.m_Matrix[3][2] = -eyeZ;
    }
}