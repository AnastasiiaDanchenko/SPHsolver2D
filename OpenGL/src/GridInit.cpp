#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include <cmath>

#include "GridInit.h"
#include "Particle.h"

float rotationAngle = 45.0f;  // Rotation angle in degrees
float rotationAngleRad = rotationAngle * M_PI / 180.0f;  // Convert to radians

// Particle container
std::vector<Particle> particles;

// Spatial partitioning
std::vector<std::vector<std::vector<Particle*>>> grid;

void UpdateGrid(const int gridSize) {
    // Clear grid
    for (auto& row : grid) {
        for (auto& col : row) {
            col.clear();
        }
    }
    // Add particles to grid
    for (int i = 0; i < particles.size(); i++) {
        int x = (particles[i].x + 1.0f) / 2.0f * gridSize;
        int y = (particles[i].y + 1.0f) / 2.0f * gridSize;

        if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) {
            continue;
        }

        grid[x][y].push_back(&particles[i]);
    }
}

void InitParticles(const int numParticles, const float spacing) {
    particles.clear();

    for (int i = 0; i < numParticles; i++) {
        for (int j = 0; j < numParticles; j++) {
            float posX = -1.0f + i * spacing + spacing / 2.0f;
            float posY = -1.0f + j * spacing + spacing / 2.0f;
            particles.push_back(Particle(posX, posY));
        }
    }
}

void RotateGrid(float angle) {
    // Convert angle from degrees to radians
    float radians = angle * M_PI / 180.0f;

    for (int i = 0; i < particles.size(); i++) {
        float x = particles[i].x;
        float y = particles[i].y;

        float rotatedX = x * cos(radians) - y * sin(radians);
        float rotatedY = x * sin(radians) + y * cos(radians);

        particles[i].x = rotatedX;
        particles[i].y = rotatedY;
    }
}

void TranslateGrid(float x, float y) {
    for (int i = 0; i < particles.size(); i++) {
		particles[i].x += x;
		particles[i].y += y;
	}
}
