//
// Created by s5614562 on 16/04/25.
//

#ifndef POINTMESH_H
#define POINTMESH_H
#include "Primitives.h"
#include "Storage/WavefrontObject.h"

namespace nsr {
class PointMesh final : public Primitive{
    float m_pointRadius = 0.1f;
    std::vector<Vec3> m_points;
public:
    PointMesh() = default;
    explicit PointMesh(const WavefrontObject& object);
    ~PointMesh() override = default;

    Hit Trace(Vec3 src, Vec3 dir, Transformation& _transform) override;
};
}





#endif //POINTMESH_H
