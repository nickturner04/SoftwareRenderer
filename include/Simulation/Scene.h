//
// Created by s5614562 on 05/03/25.
//

#ifndef SCENE_H
#define SCENE_H
#include <limits>
#include <vector>

#include "Mathematics.h"
#include "Render/Primitives.h"
#include "Storage/WavefrontObject.h"

namespace nsr {


struct ObjectHit {
    int id = 0;
    Hit hit;
};

class Material {
public:
    Material() = default;
    explicit Material(const Vec3 _colour): colour(_colour) {}
    Vec3 Shade(Hit hit) const;
    Vec3 colour = {1.f,1.f,1.f};
};

class SceneObject {
    public:
    SceneObject(Primitive& _shape, int _materialIndex): shape(_shape),materialIndex(_materialIndex){}
    Hit Trace(Vec3 src, Vec3 dir) const;
    bool enabled = true;
    Transformation transformation;
    Primitive& shape;
    int materialIndex;
};

class Camera {
public:
    Transformation transform;
    Vec3 dimensions = {12.f,9.f,20.f};

    void Rotate(const Vec3 &axis, float angle);
    void Reset();
};
//The main scene containing objects to be drawn
class Scene {
public:
    SceneObject& AddSphere(Vec3 position, float radius, Vec3 color);
    SceneObject& AddTriangle(Vec3 position,const Tri& tri, Vec3 color);
    SceneObject &AddMesh(Vec3 position, const WavefrontObject& object);
    SceneObject &AddMesh(Vec3 position, const IMeshData& data);
    SceneObject &AddPointMesh(Vec3 position, const IMeshData& object);

    //Raytrace the scene
    [[nodiscard]] ObjectHit Trace(Vec3 src, Vec3 dir) const;
    [[nodiscard]] Vec3 Shade(const ObjectHit &hit) const;
    Camera camera;
    std::vector<Primitive*> primitives;
    std::vector<Material> materials;
    std::vector<SceneObject> objects;

private:
    int index = 0;
};



} // nsr

#endif //SCENE_H
