#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include <cmath>

#include "GridInit.h"

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

void InitParticles(int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Particle p;

            p.x = -0.72f + i * SPACING + SPACING / 2.0f;
            p.y = -0.5f + j * SPACING + SPACING / 2.0f;

            particles.push_back(p);
        }
    }
}

void InitBoundaries(int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i > 2 && i < 17 && j > 2) {
                continue;
            }
            Particle p;

            p.x = -1.0f + i * SPACING + SPACING / 2.0f;
            p.y = -1.0f + j * SPACING + SPACING / 2.0f;
            p.isFluid = false;

            particles.push_back(p);
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
