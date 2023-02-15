#include "camera.h"

Camera::Camera(float aspect_ratio, float viewport_height, float focal_length) noexcept
    : m_origin{ 0.0f, 0.0f, 0.0f }
    , m_top_left{}
    , m_horizontal{}
    , m_vertical{}
{
    float viewport_width = viewport_height * aspect_ratio;

    m_horizontal = Vec3{ viewport_width, 0.0f, 0.0f };
    m_vertical   = Vec3{ 0.0f, -viewport_height, 0.0f };
    m_top_left   = m_origin - m_horizontal / 2 - m_vertical / 2 + Vec3{ 0.0f, 0.0f, focal_length };
}

Ray
Camera::ray(float u, float v) const noexcept
{
    return Ray(m_origin, m_top_left + u * m_horizontal + v * m_vertical - m_origin);
}