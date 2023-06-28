#pragma once
#include "Init.h"

void NeighborSearch() {
	for (auto& pi : particles)
	{
		pi.neighbors = 0;

		for (auto& pj : particles)
		{
			Vector2d rij = pj.x - pi.x;
			float r2 = rij.squaredNorm();
			if (r2 < 4 * SPACING * SPACING)
			{
				pi.neighbors += 1;
			}
		}
		for (auto& pk : boundaries)
		{
			Vector2d rij = pk.x - pi.x;
			float r2 = rij.squaredNorm();
			if (r2 < 4 * SPACING * SPACING)
			{
				pi.neighbors += 1;
			}
		}
	}
}