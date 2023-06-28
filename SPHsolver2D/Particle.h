#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include <Eigen/Dense>
using namespace Eigen;

struct Particle
{
	Particle(float _x, float _y) : x(_x, _y), v(0.f, 0.f), f(0.f, 0.f), rho(0), p(0.f), neighbors(0) {}
	Vector2d x, v, f;
	float rho, p;

	int neighbors;
};