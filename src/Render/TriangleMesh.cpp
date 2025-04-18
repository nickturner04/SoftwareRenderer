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
    }
}

Hit TriangleMesh::Trace(Vec3 src, Vec3 dir) {
    return {false};
}


}