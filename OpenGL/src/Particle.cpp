#include "Particle.h"

Particle::Particle() : x(0.0f), y(0.0f), vx(0.0f), vy(0.0f), ax(0.0f), ay(0.0f), mass(0.9f), density(0.0f), pressure(0.0f), isFluid(true) {}

Particle::Particle(float x, float y) : x(x), y(y), vx(0.0f), vy(0.0f), ax(0.0f), ay(0.0f), mass(0.9f), density(0.0f), pressure(0.0f), isFluid(true) {}

Particle::Particle(float x, float y, float mass) : x(x), y(y), vx(0.0f), vy(0.0f), ax(0.0f), ay(0.0f), mass(mass), density(0.0f), pressure(0.0f), isFluid(true) {}

Particle::Particle(float x, float y, float vx, float vy, float mass, float density, float pressure, bool isFluid) :
	x(x), y(y), vx(vx), vy(vy), ax(0.0f), ay(0.0f), mass(mass), density(density), pressure(pressure), isFluid(isFluid) {}
