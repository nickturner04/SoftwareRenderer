//
// Created by s5614562 on 14/04/25.
//

#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#include <cstdint>
#include <memory>

#include "Mathematics.h"
#include "Simulation/Scene.h"

namespace nsr {

class TriangleMesh : public Primitive{
public:
    TriangleMesh();
    ~TriangleMesh();
    uint32_t numFaces;
    std::unique_ptr<uint32_t[]> faceIndex;
    std::unique_ptr<uint32_t[]> vertexIndex;
    std::unique_ptr<Vec3 []> P;
};

} // nsr

#endif //TRIANGLEMESH_H
