//
// Created by s5614562 on 18/04/25.
//
#include "Render/TriangleMesh.h"
#include <algorithm>

namespace nsr {
TriangleMesh::TriangleMesh(IMeshData &mesh) {
    const auto n = mesh.triCount();
    size_t currentIndex = 0;
    for (int i = 0; i < n; ++i) {
        const auto tri = mesh.getTri(i);
        std::array<size_t, 3> face{};
        for (size_t j = 0; j < 3; ++j) {
            const auto idx = std::find(this->indexBuffer.begin(), this->indexBuffer.end(),j);
            if (idx == this->indexBuffer.end()) {
                this->vertexBuffer.push_back(tri[j]);
                face[j] = currentIndex;
                currentIndex++;
            }
            else {
                face[j] = std::distance(this->indexBuffer.begin(), idx);
            }
        }
    }
}

}