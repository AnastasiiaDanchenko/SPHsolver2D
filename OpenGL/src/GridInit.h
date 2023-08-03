#pragma once
#ifndef GRID_INIT_H
#define GRID_INIT_H

#include <iostream>
#include <vector>

#include "Particle.h"

// Initialize grid size for simulation
const int GRID_SIZE = 30;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;

// Initialize grid spacing
const float SPACING = 2.0f / GRID_SIZE;
const float SUPPORT = 2.1 * SPACING;

extern std::vector<Particle> particles;
extern std::vector<std::vector<std::vector<Particle*>>> grid;

extern void UpdateGrid();
extern void InitParticles(int width, int height);
extern void InitBoundaries(int width, int height);
extern void RotateGrid(float angle);
extern void TranslateGrid(float x, float y);

#endif