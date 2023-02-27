#include "geometry.h"

std::optional<HitResult>
Sphere::hit(const Ray& r, float t_min, float t_max) const noexcept
{
    Vec3 ray_direction = r.getDirection();
    Vec3 oc            = r.getOrigin() - m_center;
    float a            = ray_direction.length_squared();
    float b            = ray_direction.dot(oc);
    float c            = oc.length_squared() - m_radius * m_radius;
    float delta        = b * b - a * c;

    if (delta <= 0.0f)
        return std::nullopt;

    float sqrt_delta = std::sqrtf(delta);
    float root       = (-b - sqrt_delta) / a;
    if (root < t_min || t_max < root) {
        root = (-b + sqrt_delta) / a;
        if (root < t_min || t_max < root)
            return std::nullopt;
    }

    HitResult res{ .hit_point = r.at(root), .t = root, .material = m_material };
    Vec3 outward_normal = (res.hit_point - m_center) / m_radius;

    res.setFaceNormal(r, outward_normal);

    return res;
}