#pragma once

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
        DirectX::XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3 operator+(const Vec3& other) const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVectorAdd(XMLoadFloat3(&v), DirectX::XMLoadFloat3(&other.v));
        DirectX::XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3& operator+=(const Vec3& other) noexcept
    {
        auto vec = DirectX::XMVectorAdd(XMLoadFloat3(&v), DirectX::XMLoadFloat3(&other.v));
        DirectX::XMStoreFloat3(&v, vec);
        return *this;
    }

    Vec3 operator-(const Vec3& other) const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVectorSubtract(XMLoadFloat3(&v), DirectX::XMLoadFloat3(&other.v));
        DirectX::XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3& operator-=(const Vec3& other) noexcept
    {
        auto vec = DirectX::XMVectorSubtract(XMLoadFloat3(&v), DirectX::XMLoadFloat3(&other.v));
        DirectX::XMStoreFloat3(&v, vec);
        return *this;
    }

    Vec3 operator*(const Vec3& other) const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVectorMultiply(XMLoadFloat3(&v), DirectX::XMLoadFloat3(&other.v));
        DirectX::XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3& operator*=(const Vec3& other) noexcept
    {
        auto vec = DirectX::XMVectorMultiply(XMLoadFloat3(&v), DirectX::XMLoadFloat3(&other.v));
        DirectX::XMStoreFloat3(&v, vec);
        return *this;
    }

    Vec3 operator*(float r) const noexcept
    {
        auto ret = Vec3{};
        DirectX::XMStoreFloat3(&ret.v, DirectX::XMVectorScale(DirectX::XMLoadFloat3(&v), r));
        return ret;
    }

    Vec3& operator*=(float r) noexcept
    {
        DirectX::XMStoreFloat3(&v, DirectX::XMVectorScale(DirectX::XMLoadFloat3(&v), r));
        return *this;
    }

    Vec3 operator/(float r) const noexcept
    {
        auto ret = Vec3{};
        DirectX::XMStoreFloat3(&ret.v, DirectX::XMVectorScale(DirectX::XMLoadFloat3(&v), 1.0f / r));
        return ret;
    }

    Vec3& operator/=(float r) noexcept
    {
        DirectX::XMStoreFloat3(&v, DirectX::XMVectorScale(DirectX::XMLoadFloat3(&v), 1.0f / r));
        return *this;
    }

    float length() const noexcept
    {
        float ret;
        DirectX::XMStoreFloat(&ret, DirectX::XMVector3Length(XMLoadFloat3(&v)));
        return ret;
    }
    float length_squared() const noexcept
    {
        float ret;
        DirectX::XMStoreFloat(&ret, DirectX::XMVector3LengthSq(XMLoadFloat3(&v)));
        return ret;
    }

    float dot(const Vec3& other) const noexcept
    {
        float ret;
        DirectX::XMStoreFloat(&ret, DirectX::XMVector3Dot(XMLoadFloat3(&v), DirectX::XMLoadFloat3(&other.v)));
        return ret;
    }

    Vec3 cross(const Vec3& other) const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVector3Cross(XMLoadFloat3(&v), DirectX::XMLoadFloat3(&other.v));
        DirectX::XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    Vec3 normalize() const noexcept
    {
        auto ret = Vec3{};
        auto vec = DirectX::XMVector3Normalize(XMLoadFloat3(&v));
        DirectX::XMStoreFloat3(&ret.v, vec);
        return ret;
    }

    bool nearZero() const noexcept
    {
        static constexpr float s = 1e-8f;
        return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
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
