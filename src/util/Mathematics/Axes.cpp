#include "Mathematics.h"
//
// Created by s5614562 on 03/04/25.
//
std::ostream& operator<<(std::ostream &os, const Axes &_axes) {
    os << "[" << _axes.x << ", " << _axes.y << ", " << _axes.z << "]";
    return os;
}