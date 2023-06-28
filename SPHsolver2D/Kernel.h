#pragma once
#include <algorithm>
#include <Eigen/Core>

#include "Init.h"

float CubicSplineKernel(float distance, const float radius) {
    float q = distance / radius;
    float result = 0.0f;
    float alpha = 5 / (14 * M_PI * radius * radius);

    float t1 = std::max(0.0f, 1.0f - q);
    float t2 = std::max(0.0f, 2.0f - q);

    result = alpha * (t2 * t2 * t2 - 4.0f * t1 * t1 * t1);

    return result;
}

float CubicSplineKernelGradient(float distance, const float radius) {
    float q = distance / radius;
    float result = 0.0f;
    float alpha = 5 / (14 * M_PI * radius * radius);

    float t1 = std::max(0.0f, 1.0f - q);
    float t2 = std::max(0.0f, 2.0f - q);

    result = alpha * (3.0f * t2 * t2 - 12.0f * t1 * t1);

    return result;
}

float CubicSplinKernel(float distance, const float radius) {
    float result = POLY6 * pow(SPACING * SPACING - distance, 3.f);

    return result;
}

float CubicSplinKernelGradient(float distance, const float radius) {
    float result = SPIKY_GRAD * pow(SPACING - distance, 3.f);

    return result;
}