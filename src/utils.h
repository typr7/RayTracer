#pragma once

inline float
random_float() noexcept
{
    static std::random_device rd;
    static std::vector<std::mt19937> generator(thread_count, std::mt19937{rd()});
    static std::vector<std::uniform_real_distribution<float>> distribution(thread_count);
    int num = omp_get_thread_num();
    return distribution[num](generator[num]);
}

inline float
random_float(float min, float max) noexcept
{
    return min + (max - min) * random_float();
}

inline Vec3
random_vec3() noexcept
{
    return Vec3{ random_float(), random_float(), random_float() };
}

inline Vec3
random_vec3(float min, float max) noexcept
{
    return Vec3{ min, min, min } + (max - min) * random_vec3();
}

inline Vec3
random_vector_in_unit_sphere() noexcept
{
    Vec3 ret;
    while (true) {
        ret = random_vec3(-1.0f, 1.0f);
        if (ret.length_squared() <= 1.0f)
            break;
    }
    return ret;
};

inline Vec3
random_unit_vector_in_unit_sphere() noexcept
{
    return random_vector_in_unit_sphere().normalize();
};

inline Vec3
random_vector_in_unit_disk() noexcept
{
    Vec3 ret;
    while (true) {
        ret = Vec3{ random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f), 0.0f };
        if (ret.length_squared() <= 1.0f)
            break;
    }
    return ret;
}

inline Vec3
random_vector_in_unit_hemisphere(const Vec3& normal) noexcept
{
    Vec3 vec = random_vector_in_unit_sphere();
    return vec.dot(normal) > 0.0f ? vec : -vec;
};

inline Vec3
reflect(const Vec3& incident_direction, const Vec3& normal) noexcept
{
    return incident_direction - 2 * incident_direction.dot(normal) * normal;
}

inline Vec3
refract(const Vec3& incident_direction, const Vec3& normal, float etai_over_etat) noexcept
{
    float cos_theta         = fmin(normal.dot(-incident_direction), 1.0f);
    Vec3 refracted_perp     = etai_over_etat * (incident_direction + cos_theta * normal);
    Vec3 refracted_parallel = -sqrtf(fabs(1.0f - refracted_perp.length_squared())) * normal;
    return refracted_perp + refracted_parallel;
}

inline Vec3
sqrt_vec3(const Vec3& v) noexcept
{
    Vec3 ret;
    DirectX::XMVECTOR vec = DirectX::XMVectorSqrt(DirectX::XMLoadFloat3(&v.v));
    DirectX::XMStoreFloat3(&ret.v, vec);
    return ret;
}

inline Vec3
clamp_vec3(const Vec3& v, float min, float max) noexcept
{
    Vec3 ret;
    DirectX::XMVECTOR vec = DirectX::XMVectorClamp(DirectX::XMLoadFloat3(&v.v),
                                                   DirectX::XMVectorSet(min, min, min, min),
                                                   DirectX::XMVectorSet(max, max, max, max));
    DirectX::XMStoreFloat3(&ret.v, vec);
    return ret;
}