//
// Created by s5614562 on 25/04/25.
//
#include <ngl/Mat4.h>

#ifndef NGLCAMERA_H
#define NGLCAMERA_H

namespace nsr {

class NGLCamera {
    ngl::Mat4 m_view;
    ngl::Mat4 m_project;
};

} // nsi

#endif //NGLCAMERA_H
