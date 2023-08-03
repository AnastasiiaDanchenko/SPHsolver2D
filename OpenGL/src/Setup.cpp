#include "Setup.h"

void Setup() {
    //initialize particles
    InitBoundaries(GRID_WIDTH, GRID_HEIGHT);
    InitParticles(5, 5);

    UpdateGrid();

	for (int i = 0; i < particles.size(); i++) {
        // assign equal mass and rest density to all particles
        particles[i].mass = SPACING * SPACING / DENSITY;
        particles[i].density = DENSITY;
	}
}