//
// Created by s5614562 on 14/04/25.
//
#include "Render/Primitives.h"
namespace nsr {


Sphere::Sphere(const Vec3 _transform, const float _radius) {
    transform.position = _transform;
    radius = _radius;
}


Hit Sphere::Trace(Vec3 src, Vec3 dir) {
    const auto l = this->transform.position - src;
    const auto r = this->radius * transform.scale.x;
    auto tca = l.dot(dir);

    if(auto d = std::sqrt(l.dot(l) - tca * tca); d < r) {
        auto thc = std::sqrt(radius * radius - d * d);
        auto dist = tca - thc;
        auto hitPoint = src + dir * dist;
        const auto normal = (hitPoint - this->transform.position).normalized();
        return {true, dist, normal, hitPoint};
    }
    return {false, MAXFLOAT, Vec3(), Vec3()};
}

Triangle::Triangle(Vec3 _transform, const Tri &_tri): tri(_tri) {
    transform.position = _transform;
}

Hit MollerTrumbore(const Vec3 src, const Vec3 dir, const Tri &tri) {

    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    //Find Normal
    const Vec3 ab = tri.ab();
    const Vec3 ac = tri.ac();
    const Vec3 N = ab.cross(ac);

    //Step 1: Finding Hit Point

    //Check if ray is parallel to triangle
    if(std::abs(N.dot(dir)) < epsilon) {
        return {false, MAXFLOAT, N, Vec3()};
    }

    float D = -N.dot(tri.a);
    float t = -(N.dot(src) + D) / N.dot(dir);

    //Check if triangle is in front of camera.
    if(t < 0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }
    const Vec3 pHit = src + t * dir;

    float area = N.magnitude() / 2.f;

    //Step 2: Inside-Outside Test
    const Vec3 ap = pHit - tri.a;
    auto Ne = ab.cross(ap);
    const auto u = (Ne.magnitude() / 2) / area;
    if(N.dot(Ne) <0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }

    const Vec3 cb = tri.c - tri.b;
    const Vec3 bp = pHit - tri.b;
    Ne = cb.cross(bp);
    const auto v = (Ne.magnitude() / 2) / area;
    if(N.dot(Ne) <0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }

    const auto ca = tri.ca();
    const auto cp = pHit - tri.c;
    Ne = ca.cross(cp);
    if(N.dot(Ne) <0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }
    return {true, t, N, pHit,{u,v}};
}



//Uses the Moller-Trumbore method to raytrace the triangle
    //From Scratchapixel
Hit Triangle::Trace(const Vec3 src, const Vec3 dir) {

    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    const auto tri1 = this->tri.Transform(this->transform);

    //Find Normal
    const Vec3 ab = tri1.ab();
    const Vec3 ac = tri1.ac();
    const Vec3 N = ab.cross(ac);

    //Backface Culling
    if(dir.dot(N) > 0) {
        return {false};
    }

    //Step 1: Finding Hit Point

    //Check if ray is parallel to triangle
    if(std::abs(N.dot(dir)) < epsilon) {
        return {false, MAXFLOAT, N, Vec3()};
    }

    float D = -N.dot(tri1.a);
    float t = -(N.dot(src) + D) / N.dot(dir);

    //Check if triangle is in front of camera.
    if(t < 0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }
    const Vec3 pHit = src + t * dir;



    //Step 2: Inside-Outside Test
    const Vec3 ap = pHit - tri1.a;
    auto Ne = ab.cross(ap);
    if(N.dot(Ne) <0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }

    const Vec3 cb = tri1.c - tri1.b;
    const Vec3 bp = pHit - tri1.b;
    Ne = cb.cross(bp);
    if(N.dot(Ne) <0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }

    const auto ca = tri1.ca();
    const auto cp = pHit - tri1.c;
    Ne = ca.cross(cp);
    if(N.dot(Ne) <0.f) {
        return {false, MAXFLOAT, Vec3(), Vec3()};
    }
    return {true, t, N, pHit};
}

Hit SphereTrace(Vec3 src, Vec3 dir, Vec3 position, const float radius) {
    const auto l = position - src;
    auto tca = l.dot(dir);

    if(auto d = std::sqrt(l.dot(l) - tca * tca); d < radius) {
        auto thc = std::sqrt(radius * radius - d * d);
        auto dist = tca - thc;
        auto hitPoint = src + dir * dist;
        const auto normal = (hitPoint - position).normalized();
        return {true, dist, normal, hitPoint};
    }
    return {false, MAXFLOAT, Vec3(), Vec3()};
}

}