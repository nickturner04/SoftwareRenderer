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
    for (int i = 0; i < nFaces; ++i) {
        const int index = i * 3;
        const Tri tri = {vertices[indices[index]],vertices[indices[index + 1]],vertices[indices[index + 2]]};

        if (const auto hit = MollerTrumbore(src, dir, tri.Transform(this->transform)); hit.hit && hit.distance < out.distance) {out = hit;}
    }
    return out;
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