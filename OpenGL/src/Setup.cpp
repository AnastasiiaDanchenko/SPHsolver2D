#include "Setup.h"

void Setup() {
    //initialize boundary particles
    InitBoundaries(GRID_WIDTH, GRID_HEIGHT);
    InitParticles(5, 5);

    //initialize fluid particles
    /*particle p;
    p.x = -0.68f;
    p.y = -0.5f;
    particles.push_back(p);*/

    UpdateGrid();
    //RotateGrid(45.0f);
    //TranslateGrid(0.5f, 0.5f);

	for (int i = 0; i < particles.size(); i++) {
        particles[i].mass = SPACING * SPACING / DENSITY;
        particles[i].density = DENSITY;
	}
}