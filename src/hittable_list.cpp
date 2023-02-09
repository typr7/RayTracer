#include "hittable_list.h"

std::optional<HitResult>
HittableList::hit(const Ray& r, float t_min, float t_max) const noexcept
{
    std::optional<HitResult> result = std::nullopt;
    bool hit_anything               = false;
    float t_closest                 = t_max;

    for (const auto& obj : m_objects) {
        if (auto res = obj->hit(r, t_min, t_closest)) {
            result.swap(res);
            hit_anything = true;
            t_closest    = result->t;
        }
    }

    return result;
}

void
HittableList::addObject(std::shared_ptr<IHittable> object) noexcept
{
    m_objects.push_back(object);
}