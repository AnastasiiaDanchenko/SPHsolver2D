#pragma once
#include <vector>

class Particle {
public:
    float x;
    float y;
    float density;
    float pressure;

    std::vector<Particle*> neighbors;

    Particle(float x, float y);
    Particle(float x, float y, float density, float pressure);
};