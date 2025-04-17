//
// Created by s5614562 on 17/04/25.
//

#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <cstdint>
#include <vector>

#include "Mathematics.h"
#include "Primitives.h"
#include "Storage/WavefrontObject.h"

struct VertexData {
    Vec3 position;
    Vec3 normal;
    Vec2 texCoord;
};

namespace nsr {
    class TriangleMesh final : public Primitive {
    public:

        TriangleMesh() = default;
        explicit TriangleMesh(WavefrontObject &obj);
        ~TriangleMesh() override = default;
        Hit Trace(Vec3 src, Vec3 dir) override;

        uint32_t nFaces = 0;
        std::vector<VertexData> vertexBuffer;
        std::vector<uint32_t> indexBuffer;
    };
}





#endif //TRIANGLEMESH_H
