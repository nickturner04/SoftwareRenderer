#include "Render/PointMesh.h"
//
// Created by s5614562 on 16/04/25.
//
namespace nsr {
PointMesh::PointMesh(const IMeshData& mesh) {
    const size_t n = mesh.pointCount();
    for (int i = 0; i < n; ++i) {
        m_points.push_back(mesh.getPoint(i));
    }

}

Hit PointMesh::Trace(const Vec3 src, const Vec3 dir, Transformation &_transform) {
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