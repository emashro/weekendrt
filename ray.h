#pragma once

#include "vec3.h"

class ray {
public:
	ray() {}
	ray(const vec3 &a, const vec3 &b) : a(a), b(b) {}

	const vec3 &origin() const { return a; }
	const vec3 &direction() const { return b; }
	vec3 point_at_parameter(float t) const { return a + t * b; }

private:
	vec3 a; // origin
	vec3 b; // direction
};
