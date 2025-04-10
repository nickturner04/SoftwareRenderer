//
// Created by s5614562 on 27/03/25.
//
#include <valarray>

#include "Mathematics.h"


Quaternion Quaternion::LookRotation(Vec3 forward, Vec3 up) {
    auto right = forward.cross(up);

}


Quaternion Quaternion::operator*(const float _rhs) const {
    return {w * _rhs, xyz * _rhs};
}

//Function From StackExchange
//https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
//Author: Laurent Couvidou
Vec3 Quaternion::operator*(const Vec3 &_rhs) const {
    // Extract the vector part of the quaternion
    const Vec3 qv = this->VectorComponent();

    const auto uv = qv.cross(_rhs);
    const auto uuv = qv.cross(uv);
    return _rhs + ((uv * w) + uuv) * 2.f;
}

Quaternion Quaternion::operator*(const Quaternion &_rhs) const {
    return {w * _rhs.w - xyz.dot(_rhs.xyz),
        (w * _rhs.xyz) + (xyz * _rhs.w) + xyz.cross(_rhs.xyz)};
}

std::ostream& operator<<(std::ostream &os, const Quaternion &_q) {
    os << _q.w << ' ' << _q.xyz.x << ' ' << _q.xyz.y << ' ' << _q.xyz.z;
    return os;
};

Quaternion Quaternion::AxisAngle(const Vec3& axis, const float angle) {

    return{
        std::cos(angle / 2.0f),
        axis.normalized() * std::sin(angle / 2.0f)
    };
}




