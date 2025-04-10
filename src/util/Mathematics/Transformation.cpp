#include "Mathematics.h"
//
// Created by s5614562 on 03/04/25.
//
void Transformation::Rotate(const Quaternion& _rotation) {
    rotation = _rotation * rotation;
}
void Transformation::Translate(const Vec3 &translation) {
    position += translation;
}

Vec3 Transformation::forward() {
    return rotation * Vec3(0, 0, 1);
}

Vec3 Transformation::up() {
    return rotation * Vec3(0, 1, 0);
}

Axes Transformation::axes() {
    const Vec3 z = rotation * Vec3(0, 0, 1);
    const Vec3 y = rotation * Vec3(0, 1, 0);
    const Vec3 x = z.cross(y);
    return { x,y,z };
}



