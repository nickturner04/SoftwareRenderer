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
