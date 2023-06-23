#include "Computations.h"

void ComputeDensity() {
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].isFluid == false) {
			continue;
		}
		
		float density = 0.0f;
		for (int j = 0; j < particles[i].neighbors.size(); j++) {
			float dX = particles[i].x - particles[i].neighbors[j]->x;
			float dY = particles[i].y - particles[i].neighbors[j]->y;

			float distance = std::sqrt(dX * dX + dY * dY);
			
			density += particles[i].neighbors[j]->mass * CubicSplineKernel(distance, SPACING);
		}

		particles[i].density = density;
	}
}

void ComputePressure(const float stiffness) {
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].isFluid == false) {
			continue;
		}
		particles[i].pressure = std::max(0.0f, stiffness * (particles[i].density / DENSITY - 1));
		//particles[i].pressure = stiffness * (particles[i].density / DENSITY - 1);
		if (particles[i].pressure != 0 && i != 136) {
			int a = 0;
		}
	}
}

void ComputeAcceleration(const float viscosity) {
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].isFluid == false) {
			continue;
		}

		float aPressureX = 0.0f;
		float aPressureY = 0.0f;
		float aViscosityX = 0.0f;
		float aViscosityY = 0.0f;

		float aGravity = -9.81f;
		
		for (int j = 0; j < particles[i].neighbors.size(); j++) {
			float dX = particles[i].x - particles[i].neighbors[j]->x;
			float dY = particles[i].y - particles[i].neighbors[j]->y;

			float distance = std::sqrt(dX * dX + dY * dY);

			float dVX = particles[i].vx - particles[i].neighbors[j]->vx;
			float dVY = particles[i].vy - particles[i].neighbors[j]->vy;

			float dV = std::sqrt(dVX * dVX + dVY * dVY);

			aViscosityX += particles[i].neighbors[j]->mass / particles[i].neighbors[j]->density *
				dVX * dX / (dX * dX + 0.01 * SPACING * SPACING) * CubicSplineKernelGradient(distance, SPACING);

			aViscosityY += particles[i].neighbors[j]->mass / particles[i].neighbors[j]->density *
				dVY * dY / (dY * dY + 0.01 * SPACING * SPACING) * CubicSplineKernelGradient(distance, SPACING);

			if (particles[i].neighbors[j]->isFluid == false) {
				aPressureX += dX / distance * particles[i].neighbors[j]->mass * (2 * particles[i].pressure /
					(particles[i].density * particles[i].density)) * CubicSplineKernelGradient(distance, SPACING);
				aPressureY += dY / distance * particles[i].neighbors[j]->mass * (2 * particles[i].pressure /
					(particles[i].density * particles[i].density)) * CubicSplineKernelGradient(distance, SPACING);
			} else {
				if (distance == 0) {
					continue;
				} else {
					aPressureX += dX / distance * particles[i].neighbors[j]->mass * (particles[i].pressure /
						(particles[i].density * particles[i].density) + particles[i].neighbors[j]->pressure /
						(particles[i].neighbors[j]->density * particles[i].neighbors[j]->density)) *
						CubicSplineKernelGradient(distance, SPACING);
					aPressureY += dY / distance * particles[i].neighbors[j]->mass * (particles[i].pressure /
						(particles[i].density * particles[i].density) + particles[i].neighbors[j]->pressure /
						(particles[i].neighbors[j]->density * particles[i].neighbors[j]->density)) *
						CubicSplineKernelGradient(distance, SPACING);
				}
				/*aPressureX += dX * particles[i].neighbors[j]->mass * (particles[i].pressure + particles[i].neighbors[j]->pressure) /
					(2.0 * particles[i].neighbors[j]->density * particles[i].neighbors[j]->density * particles[i].density) *
					CubicSplineKernelGradient(distance, SPACING);
				aPressureY += dY * particles[i].neighbors[j]->mass * (particles[i].pressure + particles[i].neighbors[j]->pressure) /
					(2.0 * particles[i].neighbors[j]->density * particles[i].neighbors[j]->density * particles[i].density) *
					CubicSplineKernelGradient(distance, SPACING);*/
			}
		}

		particles[i].ax = - 2 * viscosity * aViscosityX + aPressureX;
		particles[i].ay = - 2 * viscosity * aViscosityY + aPressureY + aGravity;

		/*if (i == 132) {
			std::cout << "aPressureX: " << aPressureX << std::endl;
			std::cout << "aViscosityX: " << aViscosityX << std::endl;
		}*/
	}
}

void UpdateParticles(const float dt) {
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].isFluid == false) {
			continue;
		}
		particles[i].vx += particles[i].ax * dt;
		particles[i].vy += particles[i].ay * dt;
		particles[i].x += particles[i].vx * dt;
		particles[i].y += particles[i].vy * dt;

		// enforce boundary conditions
		if (particles[i].x - SPACING < -.8f)
		{
			particles[i].vx *= BOUND_DAMPING;
			//particles[i].x = SPACING;
		}
		if (particles[i].x + SPACING > 0.15f)
		{
			particles[i].vx *= BOUND_DAMPING;
			//particles[i].x = 0.15f - SPACING;
		}
		if (particles[i].y - SPACING < -.8f)
		{
			particles[i].vy *= BOUND_DAMPING;
			//particles[i].y = SPACING;
		}
		if (particles[i].y + SPACING > 1.f)
		{
			particles[i].vy *= BOUND_DAMPING;
			//particles[i].y = 1.f - SPACING;
		}
	}
}
