//
// Created by s5614562 on 06/03/25.
//

#ifndef MATHEMATICS_H
#define MATHEMATICS_H
#include <ostream>
#include <cmath>

#include "Mathematics/Matrix4f.h"

class Vec3 {
public:
    Vec3(float _x, float _y, float _z):
    x{_x},y{_y},z{_z} {}
    Vec3() = default;
    static Vec3 Zero;
    static Vec3 Up;
    static Vec3 Forward;
    static Vec3 Lerp(const Vec3 &a, const Vec3 &b, float t);
    Vec3 operator * (float _rhs) const;
    Vec3 operator * (const Vec3& _rhs) const;
    Vec3 operator / (float _rhs) const;
    Vec3 operator +(const Vec3& _rhs) const;
    Vec3 operator -(const Vec3& _rhs) const;
    Vec3 operator -() const;
    Vec3 &operator += (const Vec3& _rhs);
    Vec3 &operator *= (const Vec3& _rhs);
    Vec3 &operator *= (float _rhs);

    bool operator == (const Vec3& _rhs) const;

    Vec3 Translate(const Vec3& translation,const Vec3& forward,const Vec3&up = Up) const;
    Vec3 Rotate(const Vec3& _axis, float angle) const;

    float dot(const Vec3& _rhs) const;
    Vec3 cross(const Vec3& _rhs) const;
    Vec3 normalized() const;
    float magnitude() const;

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

inline Vec3 operator*(const float _lhs, const Vec3 & _rhs) {
    return {_lhs * _rhs.x, _lhs * _rhs.y, _lhs * _rhs.z};
}

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    Vec2 operator + (const Vec2& _rhs) const;
    bool operator == (const Vec2& _rhs) const;
};

inline Vec2 operator* (const float _lhs, const Vec2 & _rhs) {
    return {_lhs * _rhs.x, _lhs * _rhs.y};
}

struct int3 {
    int x = 0;
    int y = 0;
    int z = 0;
};

std::ostream& operator<<(std::ostream &os, const Vec3 &_q);

class Quaternion {
    public:
    Quaternion() = default;
    Quaternion(const float _w, const float _x, const float _y, const float _z):w{_w},xyz{_x,_y,_z}{}
    Quaternion(const float _w, const Vec3 _xyz): w{_w},xyz{_xyz}{}

    //Create a Quaternion from Euler angles
    static Quaternion Euler(Vec3 angles);
    static Quaternion Euler(float x, float y, float z);
    static Quaternion LookRotation(Vec3 forward, Vec3 up = Vec3(0.0f, 1.0f, 0.0f));

    //Create a Quaternion from Angle Axis
    static Quaternion AxisAngle(const Vec3& axis, float angle);

    Vec3 VectorComponent() const {return xyz;};

    //Scale a Quaternion by a float
    Quaternion operator * ( const float _rhs) const;

    //Rotate a Vec3 By a Quaternion
    Vec3 operator * (const Vec3& _rhs) const;

    //Rotate a Quaternion by a Quaternion
    Quaternion operator * (const Quaternion& _rhs) const;

    //Convert to Rotation Matrix
    Matrix4f toMatrix4f() const;

    //W is the Scalar. XYZ are the vector components.
    float w = 1.f;
    Vec3 xyz = {0.f,0.f,0.f};
};

std::ostream& operator<<(std::ostream &os, const Quaternion &_q);

struct Axes {
    Vec3 x = {1.f,0.f,0.f};
    Vec3 y = {0.f,1.f,0.f};
    Vec3 z = {0.f,0.f,1.f};
};

std::ostream& operator<<(std::ostream &os, const Axes &_axes);

class Transformation {
public:
    Vec3 position;
    Quaternion rotation;
    Vec3 scale = {1.f,1.f,1.f};

    void Rotate(const Quaternion& _rotation);
    void Translate(const Vec3& translation);
    void Scale(const Vec3& _scale);
    void Scale(float _scale);

    void TranslateLocal(const Vec3 &translation);

    Vec3 forward();
    Vec3 up();
    Axes axes();
};

struct Tri {
    Tri(const Vec3& _a, const Vec3& _b, const Vec3& _c):
    a{_a},b{_b},c{_c} {}
    Vec3 a;
    Vec3 b;
    Vec3 c;

    void Flip();
    Tri Transform(const Vec3 &_origin, const Quaternion &_rotation) const;
    Tri Transform(const Transformation &_transformation) const;
    Tri flipped() const;
    Vec3 ab() const;
    Vec3 ac() const;
    Vec3 ca() const;
    Vec3 normal() const;
};

bool TEST_QUATERNION();
#endif //MATHEMATICS_H
