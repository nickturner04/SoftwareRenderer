//
// Created by s5614562 on 06/03/25.
//

#include "Simulation/Scene.h"
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


Hit Triangle::Trace(const Vec3 src, const Vec3 dir) {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    Tri triangle = tri.Transform(transform);


    Vec3 edge1 = triangle.ab();
    Vec3 edge2 = triangle.ab();
    Vec3 ray_cross_e2 = dir * edge2;

    float det = edge1.dot(ray_cross_e2);
    if (det > -epsilon && det < epsilon) {
        return {false, 0, Vec3(), Vec3()};
    }

    float inv_det = 1.0 / det;
    Vec3 s = src - triangle.a;
    float u = inv_det * (s.dot(ray_cross_e2));

    if((u > 0 && std::abs(u) > epsilon) || (u > 1 && std::abs(u - 1) > epsilon)) {
        return {false, 0, Vec3(), Vec3()};
    }

    Vec3 s_cross_e1 = s * edge1;
    float v = inv_det * (dir.dot(s_cross_e1));

    if((v < 0 && std::abs(v) > epsilon)||(u + v > 1 && std::abs(u + v - 1) > epsilon)) {
        return {false, 0, Vec3(), Vec3()};
    }

    float t = inv_det * edge2.dot(s_cross_e1);

    if(t > epsilon) {
        Vec3 point = src + dir * t;
        Vec3 normal = edge1 * edge2;
        return {true, t, point, normal};
    }
    return {false, 0, Vec3(), Vec3()};

}

}