#pragma once
#include "Particle.h"

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

const static Vector2d G(0.f, -10.f);  

const static float REST_DENS = 900.f; //600.f //300.f
const static float STIFFNESS = 2000.f; //2000.f
const static float VISCOSITY = 1.f; //50.f //200.f
const static float TIMESTEP = 0.0003f;

const static float SPACING = 25.f;
const static float MASS = 2.5f;

static vector<Particle> particles;
static vector<Particle> boundaries;

const static int NUM_PARTICLES = 96;

const static int WINDOW_WIDTH = 800;
const static int WINDOW_HEIGHT = 600;
const static double VIEW_WIDTH = 1.5 * 800.f;
const static double VIEW_HEIGHT = 1.5 * 600.f;

const static float POLY6 = 4.f / (M_PI * pow(SPACING, 8.f));
const static float SPIKY_GRAD = -10.f / (M_PI * pow(SPACING, 5.f));
const static float VISC_LAP = 40.f / (M_PI * pow(SPACING, 5.f));

const static float EPS = SPACING;
const static float BOUND_DAMPING = -0.5f;

void InitSPH(void)
{
	for (float y = EPS + 100.f; y < VIEW_HEIGHT - EPS * 2.f; y += SPACING)
	{
		for (float x = EPS + 100.f; x <= VIEW_WIDTH / 3; x += SPACING)
		{
			if (particles.size() < NUM_PARTICLES)
			{
				float jitter = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				particles.push_back(Particle(x + jitter, y));
			}
			else
			{
				return;
			}
		}
	}
}

void InitBoundaries(void)
{
	cout << "initializing boundaries" << endl;
	for (float y = EPS * 2.f; y < 500.f; y += SPACING)
	{
		for (float x = EPS * 2.f; x < 500.f + EPS * 3.f; x += SPACING)
		{
			if (x < 90.f + EPS || y < 90.f + EPS || x > 500.f - EPS)
			{
				boundaries.push_back(Particle(x, y));
			}
		}
	}
}