//
// Created by s5614562 on 06/03/25.
//

#include "../../include/Simulation/Scene.h"
#include <cmath>
namespace nsr {

Hit SceneObject::Trace(const Vec3 src, const Vec3 dir) const {
    return shape.Trace(src, dir);
}

Vec3 Material::Shade(Hit hit) const {
    return colour;
}



SceneObject& Scene::AddSphere(const Vec3 position = {0.0f,0.f,0.f}, const float radius = 1.0f, const Vec3 color = {1.f,1.f,1.f}) {
    const auto sphere = new Sphere(position, radius);
    primitives.push_back(sphere);
    materials.emplace_back(color);
    objects.emplace_back(*primitives[this->index],index);
    index++;
    return objects[index - 1];
}

void Scene::AddTriangle(Vec3 position, const Tri &tri, Vec3 color) {
    const auto triangle = new Triangle(position, tri);
    primitives.push_back(triangle);
    materials.emplace_back(color);
    objects.emplace_back(*primitives[this->index],this->index);
    index++;
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

Vec3 Scene::Shade(const ObjectHit &hit) const {
    const auto matIndex = objects[hit.id].materialIndex;
    return materials[matIndex].Shade(hit.hit);
}

Sphere::Sphere(const Vec3 _transform, const float _radius) {
    transform = _transform;
    radius = _radius;
}


Hit Sphere::Trace(Vec3 src, Vec3 dir) {
    const auto l = this->transform - src;
    auto tca = l.dot(dir);

    if(auto d = std::sqrt(l.dot(l) - tca * tca); d < this->radius) {
        auto thc = std::sqrt(radius * radius - d * d);
        auto dist = tca - thc;
        auto hitPoint = src + dir * dist;
        const auto normal = (hitPoint - this->transform).normalized();
        return {true, dist, normal, hitPoint};
    }
    return {false, MAXFLOAT, Vec3(), Vec3()};
}

Triangle::Triangle(Vec3 _transform, const Tri &_tri): tri(_tri) {
    transform = _transform;
}

Tri Triangle::GetTriWorldSpace() {
    return {tri.a + transform, tri.b + transform, tri.c + transform};
}



Hit Triangle::Trace(const Vec3 src, const Vec3 dir) {
    /*
    Vec3 ab = tri.ab();
    Vec3 ac = tri.ac();

    Vec3 N = ab.cross(ac);

    //Check if ray is parallel to triangle
    if(std::abs(N.dot(dir)) < std::numeric_limits<float>::epsilon()) {

    }

    float D = -N.dot(tri.a);
    float t = -(N.dot(src) + D) / N.dot(dir);

    //Check if triangle is in front of camera.
    if(t < 0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }
    Vec3 pHit = src + t * dir;
    //Check if intersection is inside the triangle
    Vec3 ap = pHit - tri.a;
    if(N.dot(ab.cross(ap)) <0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }
    if(N.dot(ac.cross(ap)) <0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }
    auto ca = tri.ca();
    auto cp = pHit - tri.c;
    if(N.dot(ca.cross(cp)) <0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }
    return {true, t, N, pHit};
    */
}

}