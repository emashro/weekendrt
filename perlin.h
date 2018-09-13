#pragma once

#include "vec3.h"

class perlin {
public:
	float noise(const vec3 &p) const {
		float u = p.x() - floorf(p.x());
		float v = p.y() - floorf(p.y());
		float w = p.z() - floorf(p.z());
		int i = int(4.0f * p.x()) & 0xff;
		int j = int(4.0f * p.y()) & 0xff;
		int k = int(4.0f * p.z()) & 0xff;
		return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
	}

private:
	static float *ranfloat;
	static int *perm_x;
	static int *perm_y;
	static int *perm_z;
};
