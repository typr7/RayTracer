#include "camera.h"
#include "geometry.h"
#include "hittable_list.h"

using namespace DirectX;

void
write_color(const Vec3& color)
{
    std::cout << std::format("{} {} {} ",
                             static_cast<int>(256 * std::clamp(color.x, 0.0f, 0.999f)),
                             static_cast<int>(256 * std::clamp(color.y, 0.0f, 0.999f)),
                             static_cast<int>(256 * std::clamp(color.z, 0.0f, 0.999f)));
}

Vec3
ray_color(const Ray& r, const IHittable& world, int depth) noexcept
{
    if (depth <= 0)
        return Vec3{ 0.0f, 0.0f, 0.0f };

    auto hit_res = world.hit(r, 0.0001f, infinity);
    if (hit_res) {
        while (true) {
            if (Vec3 v = random_vec3(-1.0f, 1.0f); v.length_squared() < 1.0f) {
                Vec3 target = hit_res->hit_point + hit_res->normal + v;
                return 0.5f * ray_color(Ray{ hit_res->hit_point, target - hit_res->hit_point }, world, depth - 1);
            }
        }
        /*
        Vec3 color = (hit_res->normal + Vec3{ 1.0f, 1.0f, 1.0f }) / 2.0f;
        color.z = ((color.z * 2.0f) - 2.0f) / -2.0f;
        return color;
        */
    }

    Vec3 ur = r.getDirection().normalize();
    float t = 0.5f * (ur.y + 1.0f);

    return (1.0f - t) * Vec3{ 1.0f, 1.0f, 1.0f } + t * Vec3{ 0.5f, 0.7f, 1.0f };
}

int
main()
{
    // Image
    static constexpr float aspect_ratio        = 16.0f / 9.0f;
    static constexpr int image_width           = 960;
    static constexpr int image_height          = static_cast<int>(image_width / aspect_ratio);
    static constexpr int sample_number         = 1000;
    static constexpr float sample_offset[9][2] = { -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                                                   0.0f,  0.5f,  0.0f, -0.5f, 0.5f, 0.0f,  0.5f,  0.5f, 0.5f };
    static constexpr int max_depth             = 50;
    // Camera
    Camera camera{ 16.0f / 9.0f, 2.0f, 1.0f };

    // World
    HittableList world;
    world.addObject(std::make_shared<Sphere>(Vec3{ 0.0f, 0.0f, 1.0f }, 0.5f));
    world.addObject(std::make_shared<Sphere>(Vec3{ 0.0f, -100.5f, 1.0f }, 100.0f));

    // Render
    std::cout << std::format("P3\n{} {}\n255\n", image_width, image_height);

    for (int i = image_height - 1; i >= 0; i--) {
        std::clog << std::format("\rScanlines remaining: {}", i) << std::flush;
        for (int j = 0; j < image_width; j++) {
            Vec3 pixel_color{ 0.0f, 0.0f, 0.0f };

            for (int k = 0; k < sample_number; k++) {
                float u = (j + random_float()) / (image_width - 1);
                float v = (i + random_float()) / (image_height - 1);
                pixel_color += ray_color(camera.ray(u, v), world, max_depth);
            }

            write_color(pixel_color / sample_number);
        }
    }
    std::clog << "\nDone.\n";

    return 0;
}