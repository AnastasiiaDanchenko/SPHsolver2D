#pragma once
#include "Kernel.h"

void ComputeDensityPressure(void)
{
	for (auto& pi : particles)
	{
		pi.rho = 0.f;
		for (auto& pj : particles)
		{
			Vector2d rij = pj.x - pi.x;
			float r2 = rij.squaredNorm();

			if (r2 < SPACING * SPACING)
			{
				pi.rho += MASS * CubicSplinKernel(r2, SPACING);
			}
		}
		pi.p = STIFFNESS * (pi.rho - REST_DENS);
	}
}

void ComputeForces(void)
{
	for (auto& pi : particles)
	{
		Vector2d fpress(0.f, 0.f);
		Vector2d fvisc(0.f, 0.f);
		for (auto& pj : particles)
		{
			if (&pi == &pj)
			{
				continue;
			}

			Vector2d rij = pj.x - pi.x;
			float r = rij.norm();

			if (r < SPACING)
			{
				fpress += -rij.normalized() * MASS * (pi.p + pj.p) / (2.f * pj.rho) * CubicSplinKernelGradient(r, SPACING);
				fvisc += VISCOSITY * MASS * (pj.v - pi.v) / pj.rho * CubicSplineKernelGradient(r, SPACING);
			}
		}
		Vector2d fgrav = G * MASS / pi.rho;
		pi.f = fpress + fvisc + fgrav;
	}
}

void Integrate(void)
{
	for (auto& p : particles)
	{
		p.v += TIMESTEP * p.f / p.rho;
		p.x += TIMESTEP * p.v;

		if (STIFFNESS >= 1000.f) {
			if (p.x(0) - EPS < 100.f && p.x(1) < 500.f)
			{
				p.v(0) *= BOUND_DAMPING;
				p.x(0) = 100.f + EPS;
			}
			if (p.x(0) + EPS > 500.f && p.x(1) < 500.f)
			{
				p.v(0) *= BOUND_DAMPING;
				p.x(0) = 500.f - EPS;
			}
			if (p.x(1) - EPS < 100.f)
			{
				p.v(1) *= BOUND_DAMPING;
				p.x(1) = 100.f + EPS;
			}
		} else {
			if (p.x(0) - EPS < 100.f && p.x(1) < 500.f)
			{
				p.v(0) *= BOUND_DAMPING * (STIFFNESS - 1000.f) / 1000.f;
			}
			if (p.x(0) + EPS > 500.f && p.x(1) < 500.f)
			{
				p.v(0) *= BOUND_DAMPING * (STIFFNESS - 1000.f) / 1000.f;
			}
			if (p.x(1) - EPS < 100.f)
			{
				p.v(1) *= BOUND_DAMPING * (STIFFNESS - 1000.f) / 1000.f;
			}
		} 
	}
}