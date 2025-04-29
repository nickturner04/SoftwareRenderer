//
// Created by s5614562 on 25/04/25.
//
#include "Simulation/NGLCamera.h"
#include <ngl/Vec3.h>
#include <ngl/Util.h>

namespace nsr {
NGLCamera::NGLCamera() {
    transform.position = Vec3(0, 0, -10);

}

ngl::Mat4 NGLCamera::getViewMatrix() const {
    const auto pos = ngl::Vec3(transform.position.x,transform.position.y,transform.position.z);
    const Vec3 forward = transform.rotation * Vec3::Forward;
    const Vec3 up = transform.rotation * Vec3::Up;
    return lookAt(pos,pos + ngl::Vec3(forward.x,forward.y,forward.z),ngl::Vec3(up.x,up.y,up.z));
}

ngl::Mat4 NGLCamera::getProjectionMatrix() const {
    return ngl::perspective(45.0f,4.f/3.f,0.1f,100.0f);
}
}
