#pragma once

#include "hittable.h"

class Sphere : public IHittable
{
public:
    Sphere() noexcept : m_center{ 0.0f, 0.0f, 0.0f }, m_radius{ 1.0f } {}
    Sphere(const Vec3& center, float radius, std::shared_ptr<Material> material) noexcept
        : m_center{ center }
        , m_radius{ radius }
        , m_material{ material }
    {
    }
    virtual ~Sphere() noexcept = default;

    virtual std::optional<HitResult> hit(const Ray& r, float t_min, float t_max) const noexcept override;

private:
    Vec3 m_center;
    float m_radius;
    std::shared_ptr<Material> m_material;
};