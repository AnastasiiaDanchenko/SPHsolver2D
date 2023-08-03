#include "SimulationFalling.h"

void FallingSimulation() {
	// Choose the main parameters of the simulation
	float timestep = 0.0005f;
	const float stiffness = 1000.0f;
	const float viscosity = .1f; 

	NeighbourSearch(SUPPORT);
	ComputeDensity();
	ComputePressure(stiffness);
	ComputeAcceleration(viscosity);
	UpdateParticles(timestep);
}
