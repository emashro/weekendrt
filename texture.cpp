#include "texture.h"

vec3 image_texture::value(float u, float v, const vec3 &p) const
{
	int i = u * nx;
	int j = (1.0f - v) * ny - 0.001f;
	if (i < 0) i = 0;
	if (j < 0) j = 0;
	if (i > nx - 1) i = nx - 1;
	if (j > ny - 1) j = ny - 1;
	float r = float(data[3 * i + 3 * nx * j + 0]) / 255.0f;
	float g = float(data[3 * i + 3 * nx * j + 1]) / 255.0f;
	float b = float(data[3 * i + 3 * nx * j + 2]) / 255.0f;
	return vec3(r, g, b);
}
