#include "camera.h"
#include "geometry.h"
#include "hittable_list.h"
#include "material.h"
#include "utils.h"

using namespace DirectX;

struct R8G8B8
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

inline void
write_color(R8G8B8& dst, const Vec3& color, int sample_number) noexcept
{
    auto out_color = color / static_cast<float>(sample_number);

    out_color = sqrt_vec3(out_color);
    out_color = clamp_vec3(out_color, 0.0f, 0.999f);
    out_color *= 256.0f;

    dst.r = static_cast<uint8_t>(out_color.z);
    dst.g = static_cast<uint8_t>(out_color.y);
    dst.b = static_cast<uint8_t>(out_color.x);
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
    omp_set_num_threads(thread_count);

    // Image
    static constexpr float aspect_ratio = 16.0f / 9.0f;
    static constexpr int image_width    = 960;
    static constexpr int image_height   = static_cast<int>(image_width / aspect_ratio);
    static constexpr int max_depth      = 50;
    // static constexpr int sample_per_loop = 3;

    std::vector<Vec3> color_buffer(image_width * image_height, Vec3{ 0.0f, 0.0f, 0.0f });
    std::vector<R8G8B8> image_buffer(image_width * image_height);
    cv::Mat image;

    // Camera
    Camera camera{ 16.0f / 9.0f, 2.0f, 1.0f };

    // Material
    auto material_ground = std::make_shared<Lambertian>(Vec3{ 0.8f, 0.8f, 0.0f });
    auto material_center = std::make_shared<Lambertian>(Vec3{ 0.7f, 0.3f, 0.3f });
    auto material_left   = std::make_shared<Metal>(Vec3{ 0.8f, 0.8f, 0.8f }, 0.001f);
    auto material_right  = std::make_shared<Metal>(Vec3{ 0.8f, 0.6f, 0.2f }, 0.1f);

    // World
    HittableList world;
    world.addObject(std::make_shared<Sphere>(Vec3{ 0.0f, -100.5f, 1.0f }, 100.0f, material_ground));
    world.addObject(std::make_shared<Sphere>(Vec3{ 0.0f, 0.0f, 1.0f }, 0.5f, material_center));
    world.addObject(std::make_shared<Sphere>(Vec3{ -1.0f, 0.0f, 1.0f }, 0.5f, material_left));
    world.addObject(std::make_shared<Sphere>(Vec3{ 1.0f, 0.0f, 1.0f }, 0.5f, material_right));

    // Render
    int sample_count = 0;
    int key          = 0;
    while (key != 27) {
        if (sample_count > 100000)
            continue;
        sample_count++;
        for (int i = 0; i < image_height; i++) {
#pragma omp parallel for schedule(dynamic) \
    shared(i, image_width, image_height, image_buffer, color_buffer, camera, world, max_depth, sample_count)
            for (int j = 0; j < image_width; j++) {
                auto& color = color_buffer[i * image_width + j];

                float u = (j + random_float()) / (image_width - 1);
                float v = (i + random_float()) / (image_height - 1);
                color += ray_color(camera.ray(u, v), world, max_depth);

                write_color(image_buffer[i * image_width + j], color, sample_count);
            }
        }
        image = cv::Mat{ image_height, image_width, CV_8UC3, image_buffer.data() };
        cv::imshow("RayTracer", image);
        key = cv::waitKey(1);

        std::cout << std::format("\rsample count: {}", sample_count) << std::flush;
    }

    cv::imwrite(OUTPUT_DIR "image.png", image);
    std::cout << "\nExit.\n";

    return 0;
}