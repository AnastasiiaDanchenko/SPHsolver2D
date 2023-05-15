#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include <cmath>

#include "GridInit.h"
#include "Particle.h"

const int GRID_SIZE = 10;


float rotationAngle = 45.0f;  // Rotation angle in degrees
float rotationAngleRad = rotationAngle * M_PI / 180.0f;  // Convert to radians

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

void RotateGrid(float angle) {
    // Convert angle from degrees to radians
    float radians = angle * M_PI / 180.0f;

    // Loop over all particles
    for (int i = 0; i < particles.size(); i++) {
        // Get particle position
        float x = particles[i].x;
        float y = particles[i].y;

        // Apply rotation transformation
        float rotatedX = x * cos(radians) - y * sin(radians);
        float rotatedY = x * sin(radians) + y * cos(radians);

        // Update particle position
        particles[i].x = rotatedX;
        particles[i].y = rotatedY;
    }
}

void TranslateGrid(float x, float y) {
	// Loop over all particles
    for (int i = 0; i < particles.size(); i++) {
		// Update particle position
		particles[i].x += x;
		particles[i].y += y;
	}
}
