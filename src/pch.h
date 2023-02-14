#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <random>
#include <vector>

#include <Windows.h>
#include <omp.h>

#include "third_party/stb_image_write.h"

#include "ray.h"
#include "vec3.h"

static constexpr float infinity    = std::numeric_limits<float>::infinity();
static constexpr float pi          = DirectX::XM_PI;
static const uint32_t thread_count = omp_get_max_threads() - 1;