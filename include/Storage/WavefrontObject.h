//
// Created by s5614562 on 15/04/25.
//

#ifndef WAVEFRONTOBJECT_H
#define WAVEFRONTOBJECT_H
#include <span>
#include <string>
#include <vector>
#include "Mathematics.h"


class WavefrontObject {
private:
    struct Face {
        int vi1, vi2,vi3;
    };
    std::vector<Vec3> vertices;
    std::vector<int> vertexIndices;
    std::vector<Face> faceIndices;
public:
    explicit WavefrontObject(std::string path);
    ~WavefrontObject() = default;

    int WriteGeometry(std::string path);
    static Vec3 ParseObjVector(std::span<std::string> line);
    static Face ParseObjFace(std::span<std::string> line);
};



#endif //WAVEFRONTOBJECT_H
