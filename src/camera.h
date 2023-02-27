#pragma once

class Camera
{
public:
    Camera(Vec3 origin,
           Vec3 target,
           Vec3 up,
           float vfov,
           float aspect_ratio,
           float aperture,
           float focus_dist) noexcept;
    ~Camera() noexcept = default;

    Ray ray(float u, float v) const noexcept;

private:
    Vec3 m_origin;
    Vec3 m_top_left;
    Vec3 m_horizontal;
    Vec3 m_vertical;
    Vec3 m_u;
    Vec3 m_v;
    Vec3 m_w;
    float m_lens_radius;
};