//
// Created by s5614562 on 05/03/25.
//

#ifndef SCENE_H
#define SCENE_H
#include <limits>
#include <vector>

#include "Mathematics.h"

namespace nsr {



struct Hit {
    int hit = 0;
    float distance = std::numeric_limits<float>::max();
    Vec3 normal;
    Vec3 point;
};

struct ObjectHit {
    int id = 0;
    Hit hit;
};

class Primitive {
public:
    virtual Hit Trace(Vec3 src, Vec3 dir) = 0;
    Vec3 transform = {0.f,0.f,0.f};
};

class Sphere : public Primitive {
public:
    Sphere() = default;
    Sphere(Vec3 _transform, float _radius);
    float radius = 1.0f;
    Hit Trace(Vec3 src, Vec3 dir) override;
};

class Triangle : public Primitive {
    public:
    Triangle() = delete;
    Triangle(Vec3 _transform, const Tri &_tri);
    Hit Trace(Vec3 src, Vec3 dir) override;

    Tri tri;
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
    Primitive& shape;
    int materialIndex;
};

class Camera {
public:
    Vec3 origin = {0.f,0.f,0.f};
    Vec3 direction = {0.f,0.f,1.f};
    Vec3 dimensions = {12.f,9.f,20.f};
};

class Scene {
public:
    SceneObject& AddSphere(Vec3 position, float radius, Vec3 color);
    void AddTriangle(Vec3 position,const Tri& tri, Vec3 color);
    ObjectHit Trace(Vec3 src, Vec3 dir) const;
    Vec3 Shade(const ObjectHit &hit) const;
    Camera camera;
    std::vector<Primitive*> primitives;
    std::vector<Material> materials;
    std::vector<SceneObject> objects;

private:
    int index = 0;
};



} // nsr

#endif //SCENE_H
