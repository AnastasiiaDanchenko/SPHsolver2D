#pragma once
#ifndef GRID_INIT_H
#define GRID_INIT_H

#include <iostream>
#include <vector>

#include "Particle.h"

const int GRID_SIZE = 10;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 3;

const float SPACING = 2.0f / GRID_SIZE;
const float SUPPORT = 2.1 * SPACING;

const float VOLUME = 0.9f;
const float DENSITY = 0.8f;

extern std::vector<Particle> particles;
extern std::vector<std::vector<std::vector<Particle*>>> grid;

extern void UpdateGrid();
extern void InitParticles(int width, int height, bool isFluid);
extern void RotateGrid(float angle);
extern void TranslateGrid(float x, float y);

#endif