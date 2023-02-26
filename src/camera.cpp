#include "camera.h"

Camera::Camera(Vec3 origin, Vec3 target, Vec3 up, float vfov, float aspect_ratio) noexcept
    : m_origin{ origin }
    , m_top_left{}
    , m_horizontal{}
    , m_vertical{}
{
    float h               = tanf(vfov / 2);
    float viewport_height = 2.0f * h;
    float viewport_width  = aspect_ratio * viewport_height;

    Vec3 w = (target - origin).normalize();
    Vec3 u = up.cross(w).normalize();
    Vec3 v = w.cross(u);

    m_horizontal = viewport_width * u;
    m_vertical   = -viewport_height * v;
    m_top_left   = m_origin - m_horizontal / 2.0f - m_vertical / 2.0f + w;
}

Ray
Camera::ray(float s, float t) const noexcept
{
    return Ray(m_origin, m_top_left + s * m_horizontal + t * m_vertical - m_origin);
}