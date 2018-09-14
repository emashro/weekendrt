#pragma once

#include "vec3.h"

class perlin {
public:
	float noise(const vec3 &p) const;

private:
	static float *ranfloat;
	static int *perm_x;
	static int *perm_y;
	static int *perm_z;
};
