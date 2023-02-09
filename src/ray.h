#pragma once

#include "vec3.h"

class Ray
{
public:
    Ray() noexcept  = default;
    ~Ray() noexcept = default;

    Ray(const Vec3& origin, const Vec3& direction) noexcept : m_origin{ origin }, m_direction{ direction } {}

    Vec3 getOrigin() const noexcept { return m_origin; }
    Vec3 getDirection() const noexcept { return m_direction; }

    Vec3 at(float t) const noexcept { return m_origin + m_direction * t; }

private:
    Vec3 m_origin;
    Vec3 m_direction;
};