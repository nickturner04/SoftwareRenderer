//
// Created by s5614562 on 18/04/25.
//
#include "Render/TriangleMesh.h"
#include <algorithm>

namespace nsr {
TriangleMesh::TriangleMesh(const IMeshData &mesh) {
    const auto n = mesh.triCount();
    size_t currentIndex = 0;
    //Iterate through faces of mesh
    for (int i = 0; i < n; ++i) {
        auto tri = mesh.getTri(i);
        std::array<uint32_t, 3> face{};
        //Add vertices to vertex buffer
        for (size_t j = 0; j < 3; ++j) {
            //Search for vertex to check if it is already in the vertex buffer
            const auto idx = std::find(this->vertexBuffer.begin(), this->vertexBuffer.end(),tri[j]);
            if (idx == this->vertexBuffer.end()) {
                //Add the vertex to the buffer
                this->vertexBuffer.push_back(tri[j]);
                face[j] = currentIndex;
                currentIndex++;
            }
            else {
                //Use the existing index
                face[j] = std::distance(this->vertexBuffer.begin(), idx);
            }
        }
        //Push face onto the index buffer
        for (int j = 0; j < 3; ++j) {
            this->indexBuffer.push_back(face[j]);
        }
        this->nFaces++;
    }
}

void SmoothShade(Vec2& _st, Vec3& _n, const VertexData& v0, const VertexData& v1, const VertexData& v2) {
    //Calculate Vertex Normal
    _n = (1 - _st.x - _st.y) * v1.normal + _st.x * v2.normal + _st.y * v0.normal;

    //Calculate Texture Coordinates
    _st = (1 - _st.x - _st.y) * v2.texCoord + _st.x * v0.texCoord + _st.y * v1.texCoord;
}

Hit TriangleMesh::Trace(const Vec3 src, const Vec3 dir) {
    Hit out = {false,MAXFLOAT};
    int hitIndex = 0;
    for (int i = 0; i < nFaces; ++i) {
        const int index = i * 3;
        const Tri tri =
            Tri{vertexBuffer[indexBuffer[index]].position,
            vertexBuffer[indexBuffer[index + 1]].position,
            vertexBuffer[indexBuffer[index + 2]].position}
        .Transform(this->transform);

        if (const auto hit = MollerTrumbore(src, dir, tri); hit.hit && hit.distance < out.distance) {
            out = hit;
            hitIndex = index;
        }
    }
    if(out.hit ) {
        SmoothShade(
            out.texCoord,
            out.normal,
            vertexBuffer[indexBuffer[hitIndex]],
            vertexBuffer[indexBuffer[hitIndex + 1]],
            vertexBuffer[indexBuffer[hitIndex + 2]]);
        return out;
    }
    return {false};
}


}