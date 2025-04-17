//
// Created by s5614562 on 14/04/25.
//
#include "Render/PolygonMesh.h"
namespace nsr {

PolygonMesh::PolygonMesh(const WavefrontObject& obj): nFaces(obj.numFaces()) {
    this->vertices = obj.getVertices();
    this->normals = obj.getNormals();
    this->texCoords = obj.getTexCoords();
    this->indices.reserve(nFaces * 3);
    for (int i = 0; i < nFaces; ++i) {
        auto [a,b,c] = obj.getFaceVerts(i);
        indices.push_back(a);
        indices.push_back(b);
        indices.push_back(c);
    }
}

Hit PolygonMesh::Trace(const Vec3 src, const Vec3 dir) {
    Hit out = {false,MAXFLOAT};
    int hitIndex = 0;
    for (int i = 0; i < nFaces; ++i) {
        const int index = i * 3;
        const Tri tri = {vertices[indices[index]],vertices[indices[index + 1]],vertices[indices[index + 2]]};

        if (const auto hit = MollerTrumbore(src, dir, tri.Transform(this->transform)); hit.hit && hit.distance < out.distance) {
            out = hit;
            hitIndex = i;
        }
    }
    if(out.hit) {
        GetSurfaceData(out,hitIndex);
    }
    return out;
}

void PolygonMesh::GetSurfaceData(Hit &hit, const size_t triangleIndex) const {
    const size_t index = triangleIndex * 3;

    const auto [u, v] = hit.texCoord;

    //Calculate Texture Coordinates
    const Vec2 &st0 = texCoords[ indices[index]];
    const Vec2 &st1 = texCoords[ indices[index + 1]];
    const Vec2 &st2 = texCoords[ indices[index + 2]];
    hit.texCoord = (1 - u - v) * st0 + u * st1 + v * st2;

    //Calculate Vertex Normal
    const Vec3 &n0 = normals[ indices[index]];
    const Vec3 &n1 = normals[ indices[index + 1]];
    const Vec3 &n2 = normals[ indices[index + 2]];

    hit.normal = (1 - u - v) * n0 + u * n1 + v * n2;

}




TriangleMesh::TriangleMesh(uint32_t nfaces, int *fi, int *vi, Vec3 *v, Vec3 *n, Vec3 *st) {
    uint32_t k = 0, maxVertIndex = 0;
    for (int i = 0; i < nfaces; ++i) {
        nFaces += fi[i];
    }
}

Hit TriangleMesh::Trace(Vec3 src, Vec3 dir) {
    return {false};
}



}