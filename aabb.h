#pragma once

#include "vec3.h"
#include "ray.h"

inline float ffmin(float a, float b)
{
	return a < b ? a : b;
}

inline float ffmax(float a, float b)
{
	return a > b ? a : b;
}

class aabb {
public:
	aabb() {}
	aabb(const vec3 &a, const vec3 &b) : m_min(a), m_max(b) {}

	const vec3 &min() const { return m_min; }
	const vec3 &max() const { return m_max; }

	bool hit(const ray &r, float tmin, float tmax) const;

private:
	vec3 m_min;
	vec3 m_max;
};

aabb surrounding_box(const aabb &box0, const aabb &box1);
