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
void Transformation::Translate(float x, float y, float z) {
    position.x += x;
    position.y += y;
    position.z += z;
}
void Transformation::Scale(const Vec3 &_scale) {
    scale *= _scale;
}
void Transformation::Scale(const float _scale) {
    scale *= _scale;
}


void Transformation::TranslateLocal(const Vec3 &_translation) {
    const auto [x, y, z] = this->axes();
    this->position += x * _translation.x + y * _translation.y + z * _translation.z;
}

Vec3 Transformation::TransformPoint(const Vec3 &_point) const {
    return rotation * _point * scale + position;
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
    const Vec3 x = y.cross(z);
    return { x,y,z };
}

bool TEST_QUATERNION() {
    Transformation transformation;
    transformation.Rotate(Quaternion::AxisAngle(Vec3::Forward, M_PIf32 * 2.f * .25f * .5f));
    auto [x, y, z] = transformation.axes();
    const auto alpha = x.x;
    const auto beta = x.y;
    return y == Vec3(-beta,alpha,0.f) && z == Vec3(0,0,1.f);
}



