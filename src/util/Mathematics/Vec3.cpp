//
// Created by s5614562 on 06/03/25.
//
#include <cmath>

#include "Mathematics.h"

Vec3 Vec3::Zero = Vec3(0, 0, 0);
Vec3 Vec3::Up = Vec3(0, 1, 0);
Vec3 Vec3::Forward = Vec3(0, 0, 1);

Vec3 Vec3::operator *(float _rhs) const {
    return {x * _rhs, y * _rhs, z * _rhs};
}

Vec3 Vec3::operator*(const Vec3 &_rhs) const {
    return {x * _rhs.x, y * _rhs.y, z * _rhs.z};
}


Vec3 Vec3::operator+(const Vec3 &_rhs) const {
    return {x + _rhs.x, y + _rhs.y, z + _rhs.z};
}

Vec3 Vec3::operator-() const {
    return {-x, -y, -z};
}

Vec3 Vec3::operator-(const Vec3 &_rhs) const {
    return {x - _rhs.x, y - _rhs.y, z - _rhs.z};
}

Vec3 &Vec3::operator+=(const Vec3 &_rhs) {
    x += _rhs.x;
    y += _rhs.y;
    z += _rhs.z;
    return *this;
}

Vec3 Vec3::Translate(const Vec3 &translation, const Vec3 &forward, const Vec3 &up) const {
    const Vec3 right = forward * up;
    return *this + forward * translation.z + up * translation.y + right * translation.x;
}

Vec3 Vec3::Rotate(const Vec3 &_axis, const float angle) const {
    auto vxp =  _axis.cross(*this);
    auto vxvxp = _axis.cross(vxp);
    return *this + std::sin(angle) * vxp + (1 - std::cos(angle)) * vxvxp;
}



float Vec3::dot(const Vec3 &_rhs) const{
    return x * _rhs.x + y * _rhs.y + z * _rhs.z;
}

Vec3 Vec3::cross(const Vec3 &_rhs) const {
    return {y * _rhs.z - z * _rhs.y,x * _rhs.z - z * _rhs.x, x * _rhs.x - y * _rhs.x};
}

Vec3 Vec3::normalized() const {
    const auto mag = std::sqrt(x * x + y * y + z * z);
    return {x / mag, y / mag, z / mag};
}

float Vec3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

std::ostream& operator<<(std::ostream &os, const Vec3 &_q) {
    os << "(" << _q.x << ", " << _q.y << ", " << _q.z << ")";
    return os;
}
