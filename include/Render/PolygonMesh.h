//
// Created by s5614562 on 14/04/25.
//

#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#include <cstdint>
#include <memory>

#include "Render/Primitives.h"

namespace nsr {

class PolygonMesh{
public:
    PolygonMesh(uint32_t nfaces, int* fi, int *vi, Vec3 *p);
    ~PolygonMesh() = default;
    uint32_t numFaces;
    std::unique_ptr<uint32_t[]> faceIndex;
    std::unique_ptr<uint32_t[]> vertexIndex;
    std::unique_ptr<Vec3[]> P;
};

class TriangleMesh : public Primitive {
public:

    TriangleMesh(uint32_t nfaces, int* fi, int *vi, Vec3 *v, Vec3 *n, Vec3 *st);
    ~TriangleMesh() = default;
    Hit Trace(Vec3 src, Vec3 dir) override;

    const uint32_t nfaces;
    const std::unique_ptr<uint32_t[]> faceIndex;
    const std::unique_ptr<uint32_t[]> vertexIndex;
    const std::unique_ptr<Vec3[]> verts;
    const std::unique_ptr<Vec3[]> normals;
    const std::unique_ptr<Vec2> st;
};

} // nsr

#endif //TRIANGLEMESH_H
