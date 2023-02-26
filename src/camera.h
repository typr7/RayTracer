#pragma once

class Camera
{
public:
    Camera(Vec3 origin, Vec3 target, Vec3 up, float vfov, float aspect_ratio) noexcept;
    ~Camera() noexcept = default;

    Ray ray(float u, float v) const noexcept;

private:
    Vec3 m_origin;
    Vec3 m_top_left;
    Vec3 m_horizontal;
    Vec3 m_vertical;
};