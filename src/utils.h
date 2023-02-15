#pragma once

inline float
degrees_to_radians(float degrees) noexcept
{
    return degrees * pi / 180.0f;
}

inline float
random_float() noexcept
{
    static std::vector<std::uniform_real_distribution<float>> distribution(thread_count);
    static std::vector<std::mt19937> generator(thread_count);
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
    return Vec3{ random_float(min, max), random_float(min, max), random_float(min, max) };
}

inline Vec3
random_vector() noexcept
{
    Vec3 v;
    while (true) {
        v = random_vec3(-1.0f, 1.0f);
        if (v.length_squared() <= 1.0f)
            return v;
    }
};

inline Vec3
random_unit_vector() noexcept
{
    return random_vector().normalize();
};

inline Vec3
random_in_hemisphere(const Vec3& normal) noexcept
{
    Vec3 vec = random_vector();
    return vec.dot(normal) > 0.0f ? vec : -vec;
};

inline Vec3
reflect(const Vec3& incident_direction, const Vec3& normal) noexcept
{
    return incident_direction - 2 * incident_direction.dot(normal) * normal;
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