#pragma once
#include <vector>

class Particle {
public:
    float x;
    float y;
    float vx;
    float vy;
    float ax;
    float ay;

    float mass;
    float density;
    float pressure;

    bool isFluid;

    std::vector<Particle*> neighbors;

    Particle();
};