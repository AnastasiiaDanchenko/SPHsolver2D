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
    Particle(float x, float y);
    Particle(float x, float y, float mass);
    Particle(float x, float y, float vx, float vy, float mass, float density, float pressure, bool isFluid);
};