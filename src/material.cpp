#include "material.h"
#include "hittable.h"
#include "utils.h"

std::optional<std::pair<Ray, Vec3>>
Lambertian::scatter(const Ray& r, const HitResult& res) const noexcept
{
    Vec3 scatter_direction = res.normal + random_unit_vector();

    if (scatter_direction.nearZero())
        scatter_direction = res.normal;

    Ray scatter_ray{ res.hit_point, scatter_direction };
    return std::make_optional(std::pair(scatter_ray, m_albedo));
}

std::optional<std::pair<Ray, Vec3>>
Metal::scatter(const Ray& r, const HitResult& res) const noexcept
{
    Vec3 reflected = reflect(r.getDirection().normalize(), res.normal);
    Ray scattered{ res.hit_point, reflected + m_fuzz * random_unit_vector() };
    return scattered.getDirection().dot(res.normal) > 0 ? std::make_optional(std::pair(scattered, m_albedo))
                                                        : std::nullopt;
}