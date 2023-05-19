#include "Computations.h"

void ComputeDensity() {
	for (int i = 0; i < particles.size(); i++) {
		float density = 0.0f;
		for (int j = 0; j < particles[i].neighbors.size(); j++) {
			float dX = particles[i].x - particles[i].neighbors[j]->x;
			float dY = particles[i].y - particles[i].neighbors[j]->y;

			float distance = std::sqrt(dX * dX + dY * dY);

			density += particles[i].neighbors[j]->mass * CubicSplineKernel(distance, SUPPORT);
		}
		particles[i].density = density;
	}
}

void ComputePressure(const float stiffness) {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].pressure = stiffness * (particles[i].density / DENSITY - 1);
	}
}

void ComputeAcceleration(const float viscosity) {
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].isFluid == false) {
			continue;
		}
		float aNonPressureX = 0.0f;
		float aNonPressureY = 0.0f;

		float aPressure = 0.0f;
		float aViscosity = 0.0f;

		float aGravityY = -0.3f;
		/*
		for (int j = 0; j < particles[i].neighbors.size(); j++) {
			float dX = particles[i].x - particles[i].neighbors[j]->x;
			float dY = particles[i].y - particles[i].neighbors[j]->y;

			float distance = std::sqrt(dX * dX + dY * dY);

			float dVX = particles[i].vx - particles[i].neighbors[j]->vx;
			float dVY = particles[i].vy - particles[i].neighbors[j]->vy;

			float dV = std::sqrt(dVX * dVX + dVY * dVY);

			aViscosity += particles[i].neighbors[j]->mass / particles[i].neighbors[j]->density *
				dV * distance / (distance * distance + 0.01 * SPACING * SPACING) * 
				CubicSplineKernelGradient(distance, SUPPORT);

			aPressure -= particles[i].neighbors[j]->mass * (particles[i].pressure / 
				(particles[i].density * particles[i].density) + particles[i].neighbors[j]->pressure /
				(particles[i].neighbors[j]->density * particles[i].neighbors[j]->density)) * 
				CubicSplineKernelGradient(distance, SUPPORT);
		}

		aNonPressureX = 2 * viscosity * aViscosity;
		aNonPressureY = 2 * viscosity * aViscosity + aGravityY;

		particles[i].ax = aNonPressureX + aPressure;
		particles[i].ay = aNonPressureY + aPressure;
		*/
		particles[i].ay = aGravityY;
	}
}

void UpdateParticles(const float dt) {
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].isFluid == true) {
			if (particles[i].neighbors.size() >= 6) {
				particles[i].vy = 0.0f;
				particles[i].ay = 0.0f;
			}
		}

		particles[i].vx += particles[i].ax * dt;
		particles[i].vy += particles[i].ay * dt;
		particles[i].x += particles[i].vx * dt;
		particles[i].y += particles[i].vy * dt;
	}
}
