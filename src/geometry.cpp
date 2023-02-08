#include <cmath>

#include "geometry.hpp"

std::optional<HitResult>
Sphere::hit(const Ray& r, float t_min, float t_max) const
{
    Vec3 ray_direction = r.getDirection();
    Vec3 oc            = r.getOrigin() - m_center;
    float a            = ray_direction.length_squared();
    float b            = ray_direction.dot(oc);
    float c            = oc.length_squared() - m_radius * m_radius;
    float delta        = b * b - a * c;

    if (delta < 0.0f)
        return std::nullopt;

    float sqrt_delta = std::sqrtf(delta);
    float root       = (-b - sqrt_delta) / a;
    if (root < t_min || t_max < root) {
        root = (-b + sqrt_delta) / a;
        if (root < t_min || t_max < root)
            return std::nullopt;
    }

    HitResult res{ .hit_point = r.getOrigin() + root * ray_direction,
                   .normal    = (res.hit_point - m_center) / m_radius,
                   .t         = root };

    return res;
}