//
// Created by s5614562 on 02/04/25.
//
#include "Mathematics/Matrix4f.h"

Matrix4f Matrix4f::operator *(const Matrix4f &rhs) const{
    Matrix4f mult;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            mult[i][j] = m[i][0] * rhs[0][j] +
                m[i][1] * rhs[1][j] +
                    m[i][2] * rhs[2][j] +
                        m[i][3] * rhs[3][j];
        }
    }
    return mult;
}