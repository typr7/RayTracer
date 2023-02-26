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

std::optional<std::pair<Ray, Vec3>>
Dielectric::scatter(const Ray& r, const HitResult& res) const noexcept
{
    float refractive_indices_ratio = res.front_face ? (1.0f / m_refractive_index) : m_refractive_index;
    Vec3 unit_incident_direction   = r.getDirection().normalize();
    Vec3 normal                    = res.normal;
    float cos_theta                = fmin(normal.dot(-unit_incident_direction), 1.0f);
    float sin_theta                = sqrtf(1.0f - cos_theta * cos_theta);

    auto scattered = Vec3{};
    if (refractive_indices_ratio * sin_theta > 1.0f ||
        reflectance(cos_theta, refractive_indices_ratio) > random_float())
        scattered = reflect(unit_incident_direction, normal);
    else
        scattered = refract(unit_incident_direction, normal, refractive_indices_ratio);

    return std::make_optional(std::make_pair(Ray{ res.hit_point, scattered }, Vec3{ 1.0f, 1.0f, 1.0f }));
}

float
Dielectric::reflectance(float cos, float refractive_indices_ratio) noexcept
{
    // Use Schlick's approximation for reflectance.
    float r0 = (1.0f - refractive_indices_ratio) / (1.0f + refractive_indices_ratio);
    r0       = r0 * r0;
    return r0 + (1.0f - r0) * powf((1.0f - cos), 5.0f);
}