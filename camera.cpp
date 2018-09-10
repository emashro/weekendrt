#include "camera.h"

vec3 random_in_unit_disk()
{
	vec3 p;
	do {
		p = 2.0f * vec3(drand48(), drand48(), 0) - vec3(1.0f, 1.0f, 0.0f);
	} while (dot(p, p) >= 1.0f);
	return p;
}
