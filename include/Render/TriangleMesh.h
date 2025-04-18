//
// Created by s5614562 on 17/04/25.
//

#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <cstdint>
#include <vector>

#include "Mathematics.h"
#include "Primitives.h"
#include "Storage/IMeshData.h"


namespace nsr {
    class TriangleMesh final : public Primitive {
        uint32_t nFaces = 0;
        std::vector<VertexData> vertexBuffer;
        std::vector<uint32_t> indexBuffer;
    public:
        TriangleMesh() = default;
        explicit TriangleMesh(const IMeshData &mesh);
        ~TriangleMesh() override = default;
        Hit Trace(Vec3 src, Vec3 dir) override;
    };
}





#endif //TRIANGLEMESH_H
