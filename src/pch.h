#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <format>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <random>
#include <vector>


#include "ray.h"
#include "vec3.h"

static constexpr float infinity = std::numeric_limits<float>::infinity();
static constexpr float pi       = DirectX::XM_PI;

inline float
degrees_to_radians(float degrees)
{
    return degrees * pi / 180.0f;
}

inline float
random_float() noexcept
{
    static std::uniform_real_distribution<float> distribution{ 0.0f, 1.0f };
    static std::mt19937 generator;
    return distribution(generator);
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