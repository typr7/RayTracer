#pragma once

class Camera
{
public:
    Camera(float aspect_ratio, float viewport_height, float focal_length) noexcept;
    ~Camera() noexcept = default;

    Ray ray(float u, float v) const noexcept;

private:
    Vec3 m_origin;
    Vec3 m_bottom_left;
    Vec3 m_horizontal;
    Vec3 m_vertical;
};