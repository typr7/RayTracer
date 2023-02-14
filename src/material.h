#pragma once

struct HitResult;

class Material
{
public:
    virtual std::optional<std::pair<Ray, Vec3>> scatter(const Ray& r, const HitResult& res) const noexcept = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Vec3& albedo) : m_albedo{ albedo } {}

    virtual std::optional<std::pair<Ray, Vec3>> scatter(const Ray& r, const HitResult& res) const noexcept override;

private:
    Vec3 m_albedo;
};

class Metal : public Material
{
public:
    Metal(const Vec3& albedo, float fuzz) : m_albedo{ albedo }, m_fuzz{ fuzz < 1 ? fuzz : 1 } {}

    virtual std::optional<std::pair<Ray, Vec3>> scatter(const Ray& r, const HitResult& res) const noexcept override;

private:
    Vec3 m_albedo;
    float m_fuzz;
};