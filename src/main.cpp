#include <format>
#include <iostream>

#include "geometry.hpp"
#include "ray.hpp"
#include "vec3.hpp"

using namespace DirectX;

void
write_color(const Vec3& color)
{
    auto out_color = Vec3{ 255.999f, 255.999f, 255.999f } * color;
    std::cout << std::format("{} {} {} ",
                             static_cast<int>(out_color.x),
                             static_cast<int>(out_color.y),
                             static_cast<int>(out_color.z));
}

Vec3
ray_color(const Ray& r) noexcept
{
    static const Sphere sphere{ Vec3{ 0.0f, 0.0f, 1.0f }, 0.5f };

    Vec3 ur    = r.getDirection().normalize();
    float t    = 0.5f * (ur.y + 1.0f);
    Vec3 color = (1.0f - t) * Vec3{ 1.0f, 1.0f, 1.0f } + t * Vec3{ 0.5f, 0.7f, 1.0f };

    auto hit_res = sphere.hit(r, 0.0f, 1000.0f);
    if (hit_res) {
        color.x = (hit_res->normal.x + 1.0f) / 2.0f;
        color.y = (hit_res->normal.y + 1.0f) / 2.0f;
        color.z = (hit_res->normal.z - 1.0f) / -2.0f;
    }

    return color;
}

int
main()
{
    // Image
    static constexpr float aspect_ratio = 16.0f / 9.0f;
    static constexpr int image_width    = 960;
    static constexpr int image_height   = static_cast<int>(image_width / aspect_ratio);

    // Camera
    static constexpr float viewport_height = 2.0f;
    static constexpr float viewport_width  = aspect_ratio * viewport_height;
    static constexpr float focal_length    = 1.0f;

    auto origin      = Vec3{ 0.0f, 0.0f, 0.0f };
    auto horizontal  = Vec3{ viewport_width, 0.0f, 0.0f };
    auto vertical    = Vec3{ 0.0f, viewport_height, 0.0f };
    auto bottom_left = origin - horizontal / 2 - vertical / 2 + Vec3{ 0, 0, focal_length };

    // Render
    std::cout << std::format("P3\n{} {}\n255\n", image_width, image_height);

    for (int i = image_height - 1; i >= 0; i--) {
        for (int j = 0; j < image_width; j++) {
            auto u = static_cast<float>(j) / (image_width - 1);
            auto v = static_cast<float>(i) / (image_height - 1);
            Ray r{ origin, bottom_left + u * horizontal + v * vertical - origin };
            Vec3 pixel_color = ray_color(r);
            write_color(pixel_color);
        }
    }

    return 0;
}