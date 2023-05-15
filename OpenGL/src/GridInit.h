#pragma once
#include <iostream>
#include <vector>
#include <cmath>

const int GRID_SIZE = 10; 
float rotationAngle = 45.0f;  // Rotation angle in degrees
float rotationAngleRad = rotationAngle * M_PI / 180.0f;  // Convert to radians


class Particle {
public:
    float x;
    float y;
    std::vector<Particle*> neighbors;

    Particle(float x, float y) : x(x), y(y) {}
};

// Particle container
std::vector<Particle> particles;

// Spatial partitioning
std::vector<std::vector<std::vector<Particle*>>> grid;

void UpdateGrid() {
    // Clear grid
    for (auto& row : grid) {
        for (auto& col : row) {
            col.clear();
        }
    }
    // Add particles to grid
    for (int i = 0; i < particles.size(); i++) {
        int x = (particles[i].x + 1.0f) / 2.0f * GRID_SIZE;
        int y = (particles[i].y + 1.0f) / 2.0f * GRID_SIZE;

        if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
            continue;
        }

        grid[x][y].push_back(&particles[i]);
    }
}

void UpdateRotatedGrid() {
    // Clear grid
    for (auto& row : grid) {
        for (auto& col : row) {
            col.clear();
        }
    }

    // Apply rotation to particle positions and update grid cells
    for (int i = 0; i < particles.size(); i++) {
        // Rotate particle position
        float rotatedX = particles[i].x * cos(rotationAngleRad) - particles[i].y * sin(rotationAngleRad);
        float rotatedY = particles[i].x * sin(rotationAngleRad) + particles[i].y * cos(rotationAngleRad);

        // Get grid cell coordinates
        int x = (rotatedX + 1.0f) / 2.0f * GRID_SIZE;
        int y = (rotatedY + 1.0f) / 2.0f * GRID_SIZE;

        if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
            continue;
        }
        grid[x][y].push_back(&particles[i]);
    }
}

void InitParticles() {
    particles.clear();

    int numParticlesX = 10;
    int numParticlesY = 10;

    float spacingX = 2.0f / numParticlesX;
    float spacingY = 2.0f / numParticlesY;

    // Loop over particles and set their positions on a regular grid
    for (int i = 0; i < numParticlesX; i++) {
        for (int j = 0; j < numParticlesY; j++) {
            float posX = -1.0f + i * spacingX + spacingX / 2.0f;
            float posY = -1.0f + j * spacingY + spacingY / 2.0f;
            particles.push_back(Particle(posX, posY));
        }
    }
}

void NeighbourSearch() {
    for (int i = 0; i < particles.size(); i++) {
		particles[i].neighbors.clear();
		int x = (particles[i].x + 1.0f) / 2.0f * GRID_SIZE;
		int y = (particles[i].y + 1.0f) / 2.0f * GRID_SIZE;
		int minX = std::max(x - 2, 0);
		int maxX = std::min(x + 2, GRID_SIZE - 1);
		int minY = std::max(y - 2, 0);
		int maxY = std::min(y + 2, GRID_SIZE - 1);
        for (int j = minX; j <= maxX; j++) {
            for (int k = minY; k <= maxY; k++) {
                if (std::abs(j - x) + std::abs(k - y) >= 3) {
					continue;
				}

                for (Particle* p : grid[j][k]) {
					particles[i].neighbors.push_back(p);
				}
			}
		}
        if (particles[i].neighbors.size() == 13) {
			std::cout << "Particle " << i << " has " << particles[i].neighbors.size() << " neighbors" << std::endl;
		}
	}
}