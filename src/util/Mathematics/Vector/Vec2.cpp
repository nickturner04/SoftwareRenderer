#include "Mathematics.h"
//
// Created by s5614562 on 17/04/25.
//

bool Vec2::operator==(const Vec2& _rhs) const {
    return x == _rhs.x && y == _rhs.y;
}

Vec2 Vec2::operator+(const Vec2 &_rhs) const {
    return {x + _rhs.x, y + _rhs.y};
}
