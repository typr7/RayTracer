#pragma once

#include "hittable.h"

class HittableList : public IHittable
{
public:
    HittableList() noexcept          = default;
    virtual ~HittableList() noexcept = default;

    HittableList(const HittableList&) noexcept            = default;
    HittableList& operator=(const HittableList&) noexcept = default;

    HittableList(HittableList&&) noexcept            = default;
    HittableList& operator=(HittableList&&) noexcept = default;

    virtual std::optional<HitResult> hit(const Ray& r, float t_min, float t_max) const noexcept override;

    void addObject(std::shared_ptr<IHittable> object) noexcept;

private:
    std::vector<std::shared_ptr<IHittable>> m_objects;
};