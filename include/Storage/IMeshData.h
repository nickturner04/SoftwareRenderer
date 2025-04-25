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

    bool operator==(const VertexData & _rhs) const;
};

//Abstract class for representing a triangulated mesh, allows faces to be iterated through.
class IMeshData {
public:
    virtual ~IMeshData() = default;
    //Get Triangles(full vertex data)
    [[nodiscard]] virtual size_t triCount() const = 0;
    [[nodiscard]] virtual std::array<VertexData,3> getTri(size_t i) const = 0;

    //Get points(not full vertex data)
    [[nodiscard]] virtual size_t pointCount() const = 0;
    [[nodiscard]] virtual Vec3 getPoint(size_t i) const = 0;

};



#endif //IMESHDATA_H
