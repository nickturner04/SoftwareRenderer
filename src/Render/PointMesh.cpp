#include "Render/PointMesh.h"
//
// Created by s5614562 on 16/04/25.
//
namespace nsr {
PointMesh::PointMesh(const WavefrontObject &object) {
    this->m_points = object.getVertices();
}

Hit PointMesh::Trace(const Vec3 src, const Vec3 dir) {
    Hit out;
    for (const auto m_point : m_points) {
        if (const auto hit = SphereTrace(src,dir,m_point,m_pointRadius);
            hit.hit && hit.distance < out.distance) {
            out = hit;
        }
    }
    return out;
}


}