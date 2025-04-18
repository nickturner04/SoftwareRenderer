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


class IMeshData {
public:
    virtual ~IMeshData() = default;
    [[nodiscard]] virtual size_t triCount() const = 0;
    [[nodiscard]] virtual std::array<VertexData,3> getTri(size_t i) const = 0;

};



#endif //IMESHDATA_H
