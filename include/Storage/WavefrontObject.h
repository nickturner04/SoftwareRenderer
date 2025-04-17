//
// Created by s5614562 on 15/04/25.
//

#ifndef WAVEFRONTOBJECT_H
#define WAVEFRONTOBJECT_H
#include <string>
#include <vector>
#include "Mathematics.h"


class WavefrontObject {
public:
    struct vIndices {
        int vertex;
        int texCoord;
        int normal;
    };
    struct Face {
        vIndices a,b,c;
    };
private:
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> texCoords;
    std::vector<Face> faceIndices;

    void ParseObjLine(const std::string &line);
    static Vec3 ParseObjVector(std::string_view line);
    static Vec2 ParseObjVector2d(std::string_view line);
    static Face ParseObjFace(std::string_view line);
    static vIndices ParseObjInt3(std::string_view line);
public:
    explicit WavefrontObject(const std::string& path);
    WavefrontObject() = default;
    ~WavefrontObject() = default;

    void AddVertex(Vec3 vert, Vec2 texCoord, Vec3 normal);
    void AddVertex(float x, float y, float z);
    void AddFace(int a, int b, int c);

    int WriteGeometryToFile(std::string path);
    [[nodiscard]] size_t numFaces() const { return faceIndices.size(); }
    [[nodiscard]] size_t numVertices() const { return vertices.size(); }
    [[nodiscard]] std::vector<Vec3> const& getVertices() const { return vertices; }
    [[nodiscard]] std::vector<Vec3> const& getNormals() const { return normals; }
    [[nodiscard]] std::vector<Vec2> const& getTexCoords() const { return texCoords; }
    [[nodiscard]] int3 getFaceVerts(size_t faceIndex) const;
};



#endif //WAVEFRONTOBJECT_H
