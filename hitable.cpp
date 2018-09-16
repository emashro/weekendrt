#include "hitable.h"

void get_sphere_uv(const vec3 &p, float &u, float &v)
{
	float phi = atan2f(p.z(), p.x());
	float theta = asinf(p.y());
	u = 1.0f - (phi + M_PI) / (2.0f * M_PI);
	v = (theta + M_PI_2) / M_PI;
}
