#pragma once
#include "NeighbourSearch.h"

const static float BOUND_DAMPING = -0.5f;

void ComputeDensity();
void ComputePressure(const float stiffness);
void ComputeAcceleration(const float viscosity);
void UpdateParticles(const float timestep);
