//
// Created by s5614562 on 15/04/25.
//

#include "Storage/WavefrontObject.h"
#include <iostream>
#include <fstream>

Vec3 WavefrontObject::ParseObjVector(const std::string_view line) {
    const size_t space1 = line.find_first_of(' ');
    const size_t space2 = line.find_first_of(' ', space1 + 1);
    const auto v1 = line.substr(0, space1);
    const auto v2  = line.substr(space1 + 1, space2 - space1 - 1);
    const auto v3 = line.substr(space2 + 1, line.back());
    const Vec3 vector = {std::stof(v1.data()), std::stof(v2.data()), std::stof(v3.data()),};
    return vector;
}

Vec2 WavefrontObject::ParseObjVector2d(const std::string_view line) {
    const size_t space = line.find_first_of(' ');
    const auto v1 = line.substr(0, space);
    const auto v2  = line.substr(space + 1, line.back());
    const Vec2 vector = {std::stof(v1.data()), std::stof(v2.data())};
    return vector;
}

WavefrontObject::vIndices WavefrontObject::ParseObjInt3(const std::string_view line) {
    const size_t slash1 = line.find_first_of('/');
    const size_t slash2 = line.find_first_of('/', slash1 + 1);
    const auto v1 = line.substr(0, slash1);
    const auto v2  = line.substr(slash1 + 1, slash2 - slash1 - 1);
    const auto v3 = line.substr(slash2 + 1, line.back());
    return {std::stoi(v1.data())-1,std::stoi(v2.data())-1,std::stoi(v3.data())-1};
}


WavefrontObject::Face WavefrontObject::ParseObjFace(const std::string_view line) {
    const size_t space1 = line.find_first_of(' ');
    const size_t space2 = line.find_first_of(' ', space1 + 1);
    const auto v1 = line.substr(0, space1);
    const auto v2  = line.substr(space1 + 1, space2 - space1 - 1);
    const auto v3 = line.substr(space2 + 1, line.back());
    return {ParseObjInt3(v1), ParseObjInt3(v2), ParseObjInt3(v3)};
}


void WavefrontObject::ParseObjLine(const std::string &line) {
    switch (line[0]) {
        case 'v':
            switch (line[1]) {
                case ' ':
                    this->vertices.push_back(ParseObjVector(std::string_view(line).substr(2)));
                    break;
                case 'n':
                    this->normals.push_back(ParseObjVector(std::string_view(line).substr(3)));
                    break;
                case 't':
                    this->texCoords.push_back(ParseObjVector2d(std::string_view(line).substr(3)));
                    break;
                default:
                    break;
            }
            break;
        case 'f':
            this->faceIndices.push_back( ParseObjFace(std::string_view(line).substr(2)));
            break;
        default:
            break;
    }

}

void WavefrontObject::AddFace(const int a, const int b, const int c) {
    faceIndices.push_back(Face(vIndices{a, a, a},vIndices{b,b,b},vIndices{c,c,c}));
}

void WavefrontObject::AddVertex(const Vec3 vert, const Vec2 texCoord, const Vec3 normal) {
    vertices.push_back(vert);
    normals.push_back(normal);
    texCoords.push_back(texCoord);
}

void WavefrontObject::AddVertex(float x, float y, float z) {
    vertices.emplace_back(x,y,z);
    normals.emplace_back();
    texCoords.emplace_back();
}




WavefrontObject::WavefrontObject(const std::string& path) {
    if(auto file = std::ifstream(path); file.is_open()) {
        std::string line;
        while (getline(file,line)) {
            ParseObjLine(line);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
}


int3 WavefrontObject::getFaceVerts(const size_t faceIndex) const {
    const auto[a, b, c] = faceIndices[faceIndex];
    return {a.vertex,b.vertex,c.vertex};
}

std::array<VertexData, 3> WavefrontObject::getTri(const size_t i) const {
    const auto& [a,b,c] = this->faceIndices[i];
    const VertexData v0 = {vertices[a.vertex],normals[a.normal],texCoords[a.texCoord]};
    const VertexData v1 = {vertices[b.vertex],normals[b.normal],texCoords[b.texCoord]};
    const VertexData v2 = {vertices[c.vertex],normals[c.normal],texCoords[c.texCoord]};
    return {v0,v1,v2};
}


