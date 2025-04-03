//
// Created by s5614562 on 02/04/25.
//

#ifndef MATRIX4F_H
#define MATRIX4F_H



class Matrix4f {
public:
    Matrix4f() = default;
    const float* operator[](const int i) const {return m[i];};
    float* operator[](const int i){return m[i];};
    float m[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    Matrix4f operator*(const Matrix4f& rhs)const;
};




#endif //MATRIX4F_H
