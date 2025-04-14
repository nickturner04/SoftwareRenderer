//
// Created by s5614562 on 14/04/25.
//
#include "Render/PolygonMesh.h"
namespace nsr {

PolygonMesh::PolygonMesh(uint32_t nfaces, int *fi, int *vi, Vec3 *p):
    numFaces(nfaces), faceIndex(nullptr), vertexIndex(nullptr), P(nullptr) {
    uint32_t vertArraySize = 0;
    uint32_t maxVertexIndex = 0, index = 0;
    for (uint32_t i = 0; i < numFaces; ++i) {
        vertArraySize += fi[i];
        for (uint32_t j = 0; j < fi[i]; ++j) {
            if(vi[index + j] > maxVertexIndex) {
                maxVertexIndex = vi[index + j];
            }
        }
        index += fi[i];
    }
    maxVertexIndex += 1;

}


}