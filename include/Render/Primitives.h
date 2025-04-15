//
// Created by s5614562 on 14/04/25.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include "Mathematics.h"

namespace nsr {

    struct Hit {
        int hit = 0;
        float distance = std::numeric_limits<float>::max();
        Vec3 normal;
        Vec3 point;
    };
    class Primitive {
    public:
        virtual ~Primitive() = default;
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
        Tri GetTriWorldSpace();
    private:
        Tri tri;
    };

    Hit MollerTrumbore(Vec3 src, Vec3 dir, const Tri &tri);
}
#endif //PRIMITIVES_H
