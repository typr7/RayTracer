#ifndef RAYTRACER_HITTABLE_HPP
#define RAYTRACER_HITTABLE_HPP

#include <optional>

#include "ray.hpp"
#include "vec3.hpp"

struct HitResult
{
    Vec3 hit_point;
    Vec3 normal;
    float t;
};

struct IHittable
{
    virtual std::optional<HitResult> hit(const Ray& r, float t_min, float t_max) const = 0;
    virtual ~IHittable() noexcept                                                      = default;
};

#endif