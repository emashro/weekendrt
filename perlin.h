#pragma once

#include "vec3.h"

class perlin {
public:
	float noise(const vec3 &p) const;
	float turb(const vec3 &p, int depth = 7) const;

private:
	static vec3 *ranvec;
	static int *perm_x;
	static int *perm_y;
	static int *perm_z;
};
