#include "SimulationFalling.h"

void FallingSimulation(const float support) {
	float timestep = 0.01f;
	const float stiffness = 1.1f;
	const float viscosity = 1.2f;

	NeighbourSearch(support);
	ComputeDensity();
	ComputePressure(stiffness);
	ComputeAcceleration(viscosity);
	UpdateParticles(timestep);
}