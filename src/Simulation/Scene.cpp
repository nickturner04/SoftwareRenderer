//
// Created by s5614562 on 06/03/25.
//

#include "../../include/Simulation/Scene.h"
#include <cmath>

#include "Render/PointMesh.h"
#include "Render/PolygonMesh.h"
#include "Render/TriangleMesh.h"

namespace nsr {

Vec3 Scene::Shade(const ObjectHit &hit) const {
    const auto matIndex = objects[hit.id].materialIndex;
    return materials[matIndex].Shade(hit.hit);
}

Hit SceneObject::Trace(const Vec3 src, const Vec3 dir) const {
    Transformation x = this->transformation;
    return shape.Trace(src, dir,x);
}

Vec3 Material::Shade(Hit hit) const {
    return colour;
}



SceneObject& Scene::AddSphere(const Vec3 position = {0.0f,0.f,0.f}, const float radius = 1.0f, const Vec3 color = {1.f,1.f,1.f}) {
    const auto sphere = new Sphere(radius);
    primitives.push_back(sphere);
    materials.emplace_back(color);
    objects.emplace_back(*primitives[this->index],index);
    index++;
    return objects[index - 1];
}

SceneObject& Scene::AddTriangle(Vec3 position, const Tri &tri, Vec3 color) {
    const auto triangle = new Triangle(position, tri);
    primitives.push_back(triangle);
    materials.emplace_back(color);
    objects.emplace_back(*primitives[this->index],this->index);
    index++;
    return objects[index - 1];
}

SceneObject &Scene::AddMesh(const Vec3 position, const WavefrontObject& object) {
    const auto mesh = new PolygonMesh(object);
    primitives.push_back(mesh);
    materials.emplace_back(Vec3(1,1,1));
    objects.emplace_back(*primitives[this->index],this->index).transformation.position = position;
    index++;
    return objects[this->index - 1];
}

SceneObject &Scene::AddMesh(const Vec3 position, const IMeshData &data) {
    const auto mesh = new TriangleMesh(data);
    primitives.push_back(mesh);
    materials.emplace_back(Vec3(1,1,1));
    objects.emplace_back(*primitives[this->index],this->index).transformation.position = position;
    index++;
    return objects[this->index - 1];
}


SceneObject &Scene::AddPointMesh(const Vec3 position, const WavefrontObject &object) {
    const auto mesh = new PointMesh(object);
    primitives.push_back(mesh);
    materials.emplace_back(Vec3(1,1,1));
    objects.emplace_back(*primitives[this->index],this->index).transformation.position = position;
    index++;
    return objects[this->index - 1];

}




ObjectHit Scene::Trace(const Vec3 src, const Vec3 dir) const {
    ObjectHit result;
    for (int i = 0; i < objects.size(); ++i) {
        if(!objects[i].enabled)continue;
        auto hit = objects[i].Trace(src, dir);
        if (hit.hit && hit.distance < result.hit.distance && hit.distance > 0.f) {
            result.id = i;
            result.hit = hit;
        }
    }
    return result;
}



}
