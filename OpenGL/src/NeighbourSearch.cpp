#include "NeighbourSearch.h"

const float NEIGHBOR_RADIUS = 0.41f;

void NeighbourSearch() {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].neighbors.clear();

		for (int j = 0; j < particles.size(); j++) {
			float dx = particles[j].x - particles[i].x;
			float dy = particles[j].y - particles[i].y;
			float distance = std::sqrt(dx * dx + dy * dy);

			if (distance < NEIGHBOR_RADIUS) {
				particles[i].neighbors.push_back(&particles[j]);
			}
		}

		std::cout << "Particle " << i << " has " << particles[i].neighbors.size() << " neighbors. "
			<< "Position: (" << particles[i].x << ", " << particles[i].y << ")" << std::endl;
	}
}