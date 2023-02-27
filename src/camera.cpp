#include "camera.h"
#include "utils.h"

Camera::Camera(Vec3 origin,
               Vec3 target,
               Vec3 up,
               float vfov,
               float aspect_ratio,
               float aperture,
               float focus_dist) noexcept
    : m_origin{ origin }
    , m_top_left{}
    , m_horizontal{}
    , m_vertical{}
    , m_u{}
    , m_v{}
    , m_w{}
    , m_lens_radius{ aperture / 2.0f }
{
    float h               = tanf(vfov / 2);
    float viewport_height = 2.0f * h;
    float viewport_width  = aspect_ratio * viewport_height;

    m_w = (target - origin).normalize();
    m_u = up.cross(m_w).normalize();
    m_v = m_w.cross(m_u);

    m_horizontal = focus_dist * viewport_width * m_u;
    m_vertical   = focus_dist * -viewport_height * m_v;
    m_top_left   = m_origin - m_horizontal / 2.0f - m_vertical / 2.0f + focus_dist * m_w;
}

Ray
Camera::ray(float s, float t) const noexcept
{
    Vec3 rd     = m_lens_radius * random_vector_in_unit_disk();
    Vec3 origin = m_u * rd.x + m_v * rd.y + m_origin;

    return Ray{ origin, m_top_left + s * m_horizontal + t * m_vertical - origin };
}