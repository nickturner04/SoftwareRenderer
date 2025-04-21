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
        Vec2 texCoord;
    };
    class Primitive {
    public:
        virtual ~Primitive() = default;
        virtual Hit Trace(Vec3 src, Vec3 dir,Transformation &_transform) = 0;
    };

    class Sphere final : public Primitive {
    public:
        Sphere() = default;
        explicit Sphere(float _radius);
        float radius = 1.0f;
        Hit Trace(Vec3 src, Vec3 dir,Transformation &_transform) override;
    };

    class Triangle final : public Primitive {
    public:
        Triangle() = delete;
        Triangle(Vec3 _transform, const Tri &_tri);
        Hit Trace(Vec3 src, Vec3 dir, Transformation &_transform) override;
    private:
        Tri tri;
    };

    Hit MollerTrumbore(Vec3 src, Vec3 dir, const Tri &tri);
    Hit SphereTrace(Vec3 src, Vec3 dir, Vec3 position, float radius);
}
#endif //PRIMITIVES_H
