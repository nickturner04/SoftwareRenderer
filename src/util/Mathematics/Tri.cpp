//
// Created by s5614562 on 13/03/25.
//
#include "Mathematics.h"


Tri Tri::Transform(const Vec3 &_origin, const Quaternion &_rotation) const {
    return {_rotation * a + _origin, _rotation * b + _origin, _rotation * c + _origin};
}
Tri Tri::Transform(const Transformation &_transformation) const {
    return {_transformation.rotation * a * _transformation.scale + _transformation.position , _transformation.rotation * b * _transformation.scale + _transformation.position, _transformation.rotation * c * _transformation.scale + _transformation.position};
}

Vec3 Tri::ab() const {
    return b - a;
}
Vec3 Tri::ac() const {
    return c - a;
}

Vec3 Tri::normal() const {
    return ab().cross(ac());
}

Vec3 Tri::ca() const {
    return a - c;
}


Tri Tri::flipped() const {
    const auto tmp = *this;
    return  Tri(tmp.c,tmp.b,tmp.a);
}


void Tri::Flip() {
    auto tmp = *this;
    *this = Tri(tmp.c,tmp.b,tmp.a);
}



