#pragma once
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#include "Setup.h"

float CubicSplineKernel(float r, const float radius);
float CubicSplineKernelGradient(float r, const float radius);

void KernelTest(const float radius, const int numParticles);
