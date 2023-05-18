#include "Particle.h"

Particle::Particle(float x, float y) : x(x), y(y), density(0.0f), pressure(0.0f) {}

Particle::Particle(float x, float y, float density, float pressure) :
	x(x), y(y), density(density), pressure(pressure) {}
