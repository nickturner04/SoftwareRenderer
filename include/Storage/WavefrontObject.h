//
// Created by s5614562 on 15/04/25.
//

#ifndef WAVEFRONTOBJECT_H
#define WAVEFRONTOBJECT_H
#include <string>
#include <vector>
#include "Mathematics.h"


class WavefrontObject {
    struct vIndices {
        int vertex;
        int texCoord;
        int normal;
    };
    struct Face {
        vIndices a,b,c;
    };
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec3> texCoords;
    std::vector<Face> faceIndices;

    void ParseObjLine(const std::string &line);
    static Vec3 ParseObjVector(std::string_view line);
    static Face ParseObjFace(std::string_view line);
    static vIndices ParseObjInt3(std::string_view line);
public:
    explicit WavefrontObject(const std::string& path);
    ~WavefrontObject() = default;

    int WriteGeometry(std::string path);
    [[nodiscard]] size_t numFaces() const { return faceIndices.size(); }
    [[nodiscard]] size_t numVertices() const { return vertices.size(); }
    [[nodiscard]] std::vector<Vec3> const& getVertices() const { return vertices; }
    [[nodiscard]] int3 getFaceVerts(size_t faceIndex) const;
};



#endif //WAVEFRONTOBJECT_H
