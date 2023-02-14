#pragma once

class Material;

struct HitResult
{
    Vec3 hit_point;
    Vec3 normal;
    float t;
    std::shared_ptr<Material> material;
    bool front_face;

    inline void setFaceNormal(const Ray& r, const Vec3& outward_normal) noexcept
    {
        front_face = r.getDirection().dot(outward_normal) < 0.0f;
        normal     = front_face ? outward_normal : -outward_normal;
    }
};

struct IHittable
{
    virtual ~IHittable() noexcept = default;

    virtual std::optional<HitResult> hit(const Ray& r, float t_min, float t_max) const noexcept = 0;
};