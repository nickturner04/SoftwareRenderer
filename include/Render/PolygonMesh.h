//
// Created by s5614562 on 14/04/25.
//

#ifndef POLYGONMESH_H
#define POLYGONMESH_H
#include <cstdint>
#include <memory>

#include "Render/Primitives.h"
#include "Storage/WavefrontObject.h"

namespace nsr {

class PolygonMesh final : public Primitive{
    uint32_t nFaces;
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> texCoords;
    std::vector<uint32_t> indices;
public:
    explicit PolygonMesh(const WavefrontObject& obj);
    ~PolygonMesh() override = default;
    Hit Trace(Vec3 src, Vec3 dir,Transformation &_transform) override;
    void GetSurfaceData(Hit &hit, size_t triangleIndex) const;
};

} // nsr

#endif //POLYGONMESH_H
