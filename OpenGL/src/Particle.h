#pragma once
#include <vector>

class Particle {
public:
    float x;
    float y;
    std::vector<Particle*> neighbors;

    Particle(float x, float y);
};