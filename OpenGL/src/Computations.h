#pragma once
#include "NeighbourSearch.h"

void ComputeDensity();
void ComputePressure(const float stiffness);
void ComputeAcceleration(const float viscosity);
void UpdateParticles(const float timestep);
