//
// Created by s5614562 on 13/03/25.
//
#include "Mathematics.h"


Tri Tri::Transform(const Vec3 &_origin, const Quaternion &_rotation) const {
    return {_rotation * a + _origin, _rotation * b + _origin, _rotation * c + _origin};
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


Tri Tri::flipped() const {
    const auto tmp = *this;
    return  Tri(tmp.c,tmp.b,tmp.a);
}


void Tri::Flip() {
    auto tmp = *this;
    *this = Tri(tmp.c,tmp.b,tmp.a);
}



