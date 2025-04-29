//
// Created by s5614562 on 25/04/25.
//


#ifndef NGLCAMERA_H
#define NGLCAMERA_H

#include <ngl/Mat4.h>
#include <Mathematics.h>

namespace nsr {

class NGLCamera {
    public:
    NGLCamera();
    Transformation transform;
    [[nodiscard]] ngl::Mat4 getViewMatrix() const;
    [[nodiscard]] ngl::Mat4 getProjectionMatrix() const;
};

} // nsi

#endif //NGLCAMERA_H
