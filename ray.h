#pragma once

#include "vec3.h"

class ray {
public:
	ray() {}
	ray(const vec3 &a, const vec3 &b, float time = 0.0f) : m_a(a), m_b(b), m_time(time) {}

	const vec3 &origin() const { return m_a; }
	const vec3 &direction() const { return m_b; }
	float time() const { return m_time; }
	vec3 point_at_parameter(float t) const { return m_a + t * m_b; }

private:
	vec3 m_a; // origin
	vec3 m_b; // direction
	float m_time;
};
