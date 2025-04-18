#include "Storage/IMeshData.h"
//
// Created by s5614562 on 18/04/25.
//
bool VertexData::operator==(const VertexData & _rhs) const {
    return {position == _rhs.position && normal == _rhs.normal && texCoord == _rhs.texCoord};
}