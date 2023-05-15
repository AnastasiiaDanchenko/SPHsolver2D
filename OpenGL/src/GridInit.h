#ifndef GRID_INIT_H
#define GRID_INIT_H

#include <iostream>
#include <vector>

#include "Particle.h"

extern const int GRID_SIZE;
extern float rotationAngle;
extern float rotationAngleRad;

extern std::vector<Particle> particles;
extern std::vector<std::vector<std::vector<Particle*>>> grid;

extern void UpdateGrid();
extern void InitParticles();
extern void RotateGrid(float angle);
extern void TranslateGrid(float x, float y);

#endif