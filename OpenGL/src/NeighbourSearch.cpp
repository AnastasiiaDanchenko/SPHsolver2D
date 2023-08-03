#include "NeighbourSearch.h"

// Neighbour search
void NeighbourSearch(const float radius) {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].neighbors.clear();

		for (int j = 0; j < particles.size(); j++) {
			float dx = particles[j].x - particles[i].x;
			float dy = particles[j].y - particles[i].y;
			float distance = std::sqrt(dx * dx + dy * dy);

			if (distance < radius) {
				particles[i].neighbors.push_back(&particles[j]);
			}
		}
	}
}
