//
// Created by s5614562 on 14/04/25.
//

#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#include <cstdint>
#include <memory>

#include "Render/Primitives.h"
#include "Storage/WavefrontObject.h"

namespace nsr {

class PolygonMesh final : public Primitive{
    uint32_t nFaces;
    std::vector<Vec3> vertices;
    std::vector<uint32_t> indices;
public:
    explicit PolygonMesh(const WavefrontObject& obj);
    ~PolygonMesh() override = default;
    Hit Trace(Vec3 src, Vec3 dir) override;
};

class TriangleMesh final : public Primitive {
public:

    TriangleMesh(uint32_t nfaces, int* fi, int *vi, Vec3 *v, Vec3 *n, Vec3 *st);
    ~TriangleMesh() = default;
    Hit Trace(Vec3 src, Vec3 dir) override;

    uint32_t nFaces;
    const std::unique_ptr<uint32_t[]> faceIndex;
    const std::unique_ptr<uint32_t[]> vertexIndex;
    const std::unique_ptr<Vec3[]> verts;
    const std::unique_ptr<Vec3[]> normals;
    const std::unique_ptr<Vec2> st;
};

} // nsr

#endif //TRIANGLEMESH_H
