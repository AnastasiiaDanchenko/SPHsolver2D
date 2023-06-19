#include "SimulationFalling.h"

void FallingSimulation() {
	float timestep = 0.001f; //0.001 
	//0.1 - no particle; 0.01 - unstable
	//0.0001 - looses energy too slow

	const float stiffness = 500.0f; //270 or 2500
	// <250 - pressure too small, collides with boundary
	// 10000 - unstable, looses/gains energy; 25000 - gains energy

	const float viscosity = 0.2f; //60
	// 10 - bounces infinitely
	// 6000 - gains 

	NeighbourSearch(SUPPORT);
	ComputeDensity();
	ComputePressure(stiffness);
	ComputeAcceleration(viscosity);
	UpdateParticles(timestep);
}
