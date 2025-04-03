#include "Simulation/Scene.h"
//
// Created by s5614562 on 03/04/25.
//
namespace nsr{
    void Camera::Rotate(const Vec3& axis, const float angle) {
        const Quaternion rotation = Quaternion::AxisAngle(axis, angle);
        transform.Rotate(rotation);
    }
}