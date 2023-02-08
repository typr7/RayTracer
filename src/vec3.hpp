#ifndef RAYTRACER_VEC3_HPP
#define RAYTRACER_VEC3_HPP

#include <DirectXMath.h>

struct Vec3;

struct Vec3
{
public:
    Vec3() noexcept  = default;
    ~Vec3() noexcept = default;

    Vec3(const Vec3&) noexcept            = default;
    Vec3& operator=(const Vec3&) noexcept = default;

    Vec3(Vec3&&) noexcept            = default;
    Vec3& operator=(Vec3&&) noexcept = default;

    Vec3(float x, float y, float z) noexcept : v{ x, y, z } {}

    float operator[](size_t i) const noexcept { return reinterpret_cast<const float*>(this)[i]; }
    float& operator[](size_t i) noexcept { return reinterpret_cast<float*>(this)[i]; }

    Vec3 operator-() const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVectorNegate(XMLoadFloat3(&v));
        XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3 operator+(const Vec3& other) const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVectorAdd(XMLoadFloat3(&v), XMLoadFloat3(&other.v));
        XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3& operator+=(const Vec3& other) noexcept
    {
        auto vec = DirectX::XMVectorAdd(XMLoadFloat3(&v), XMLoadFloat3(&other.v));
        XMStoreFloat3(&v, vec);
        return *this;
    }

    Vec3 operator-(const Vec3& other) const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVectorSubtract(XMLoadFloat3(&v), XMLoadFloat3(&other.v));
        XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3& operator-=(const Vec3& other) noexcept
    {
        auto vec = DirectX::XMVectorSubtract(XMLoadFloat3(&v), XMLoadFloat3(&other.v));
        XMStoreFloat3(&v, vec);
        return *this;
    }

    Vec3 operator*(const Vec3& other) const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVectorMultiply(XMLoadFloat3(&v), XMLoadFloat3(&other.v));
        XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3& operator*=(const Vec3& other) noexcept
    {
        auto vec = DirectX::XMVectorMultiply(XMLoadFloat3(&v), XMLoadFloat3(&other.v));
        XMStoreFloat3(&v, vec);
        return *this;
    }

    Vec3 operator*(float r) const noexcept
    {
        auto ret = Vec3{};
        XMStoreFloat3(&ret.v, XMLoadFloat3(&v) * r);
        return ret;
    }

    Vec3& operator*=(float r) noexcept
    {
        XMStoreFloat3(&v, XMLoadFloat3(&v) * r);
        return *this;
    }

    Vec3 operator/(float r) const noexcept
    {
        auto ret = Vec3{};
        XMStoreFloat3(&ret.v, XMLoadFloat3(&v) / r);
        return ret;
    }

    Vec3& operator/=(float r) noexcept
    {
        XMStoreFloat3(&v, XMLoadFloat3(&v) / r);
        return *this;
    }

    float length() const noexcept { return DirectX::XMVector3Length(XMLoadFloat3(&v))[0]; }
    float length_squared() const noexcept { return DirectX::XMVector3LengthSq(XMLoadFloat3(&v))[0]; }

    float dot(const Vec3& other) const noexcept
    {
        return DirectX::XMVector3Dot(XMLoadFloat3(&v), XMLoadFloat3(&other.v))[0];
    }

    Vec3 cross(const Vec3& other) const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVector3Cross(XMLoadFloat3(&v), XMLoadFloat3(&other.v));
        XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3 normalize() const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVector3Normalize(XMLoadFloat3(&v));
        XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    union
    {
        DirectX::XMFLOAT3 v;
        struct
        {
            float x;
            float y;
            float z;
        };
    };
};

inline Vec3
operator*(float r, const Vec3& v) noexcept
{
    return v * r;
}

#endif