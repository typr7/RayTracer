#include "camera.h"
#include "geometry.h"
#include "hittable_list.h"
#include "material.h"
#include "utils.h"

using namespace DirectX;

inline void
write_color(std::vector<uint8_t>& dst, int index, const Vec3& color, int sample_number)
{
    auto out_color = color / static_cast<float>(sample_number);

    out_color.x = std::sqrtf(out_color.x);
    out_color.y = std::sqrtf(out_color.y);
    out_color.z = std::sqrtf(out_color.z);

    dst[index]     = static_cast<uint8_t>(256 * std::clamp(out_color.x, 0.0f, 0.999f));
    dst[index + 1] = static_cast<uint8_t>(256 * std::clamp(out_color.y, 0.0f, 0.999f));
    dst[index + 2] = static_cast<uint8_t>(256 * std::clamp(out_color.z, 0.0f, 0.999f));
}

Vec3
ray_color(const Ray& r, const IHittable& world, int depth) noexcept
{
    if (depth <= 0)
        return Vec3{ 0.0f, 0.0f, 0.0f };

    if (auto hit_res = world.hit(r, 0.0001f, infinity)) {
        if (auto scatter_res = hit_res->material->scatter(r, *hit_res))
            return scatter_res->second * ray_color(scatter_res->first, world, depth - 1);
        return Vec3{ 0.0f, 0.0f, 0.0f };
    }

    Vec3 ur = r.getDirection().normalize();
    float t = 0.5f * (ur.y + 1.0f);

    return (1.0f - t) * Vec3{ 1.0f, 1.0f, 1.0f } + t * Vec3{ 0.5f, 0.7f, 1.0f };
}

int
main()
{
    // Image
    static constexpr float aspect_ratio = 16.0f / 9.0f;
    static constexpr int image_width    = 960;
    static constexpr int image_height   = static_cast<int>(image_width / aspect_ratio);
    static constexpr int sample_number  = 1000;
    static constexpr int max_depth      = 50;

    std::vector<uint8_t> image_buffer(image_width * image_height * 3);

    // Camera
    Camera camera{ 16.0f / 9.0f, 2.0f, 1.0f };

    // Material
    auto material_ground = std::make_shared<Lambertian>(Vec3{0.8f, 0.8f, 0.0f});
    auto material_center = std::make_shared<Lambertian>(Vec3{0.7f, 0.3f, 0.3f});
    auto material_left   = std::make_shared<Metal>(Vec3{0.8f, 0.8f, 0.8f}, 0.001f);
    auto material_right  = std::make_shared<Metal>(Vec3{0.8f, 0.6f, 0.2f}, 0.1f);

    // World
    HittableList world;
    world.addObject(std::make_shared<Sphere>(Vec3{ 0.0f, -100.5f, 1.0f }, 100.0f, material_ground));
    world.addObject(std::make_shared<Sphere>(Vec3{ 0.0f, 0.0f, 1.0f }, 0.5f, material_center));
    world.addObject(std::make_shared<Sphere>(Vec3{ -1.0f, 0.0f, 1.0f }, 0.5f, material_left));
    world.addObject(std::make_shared<Sphere>(Vec3{ 1.0f, 0.0f, 1.0f }, 0.5f, material_right));

    // Timer
    LARGE_INTEGER t1, t2, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&t1);

    // Render
    omp_set_num_threads(thread_count);
    int remain = image_height;
    for (int i = 0; i < image_height; i++) {
        --remain;
        std::cout << std::format("\rScanlines remaining: {:4d}", remain) << std::flush;
#pragma omp parallel for schedule(dynamic) shared(image_buffer)
        for (int j = 0; j < image_width; j++) {
            Vec3 pixel_color{ 0.0f, 0.0f, 0.0f };

            for (int k = 0; k < sample_number; k++) {
                float u = (j + random_float()) / (image_width - 1);
                float v = (i + random_float()) / (image_height - 1);
                pixel_color += ray_color(camera.ray(u, v), world, max_depth);
            }

            write_color(image_buffer, (i * image_width + j) * 3, pixel_color, sample_number);
        }
    }

    QueryPerformanceCounter(&t2);

    stbi_write_png(OUTPUT_DIR"image.png", image_width, image_height, 3, image_buffer.data(), image_width * 3);
    std::cout << "\nDone.\n";
    std::cout << std::format("number of computation threads: {}\n", thread_count);
    std::cout << std::format("time: {}\n", (t2.QuadPart - t1.QuadPart) / static_cast<double>(freq.QuadPart));

    return 0;
}