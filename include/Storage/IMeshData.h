//
// Created by s5614562 on 18/04/25.
//

#ifndef IMESHDATA_H
#define IMESHDATA_H
#include "Mathematics.h"
#include<array>

struct VertexData {
    Vec3 position;
    Vec3 normal;
    Vec2 texCoord;
};

class IMeshData {
public:
    virtual ~IMeshData() = 0;
    virtual int triCount() = 0;
    virtual std::array<VertexData,3> getTri(size_t i);

};



#endif //ITRIANGLEMESH_H
