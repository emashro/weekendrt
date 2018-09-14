#include "perlin.h"

static float *perlin_generate()
{
	float *p = new float[256];
	for (int i = 0; i < 256; i++) {
		p[i] = drand48();
	}
	return p;
}

static void permute(int *p, int n)
{
	for (int i = n - 1; i > 0; i--) {
		int target = int(drand48() * float(i + 1));
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
}

static int *perlin_generate_perm()
{
	int *p = new int[256];
	for (int i = 0; i < 256; i++) {
		p[i] = i;
	}
	permute(p, 256);
	return p;
}

float *perlin::ranfloat = perlin_generate();
int *perlin::perm_x = perlin_generate_perm();
int *perlin::perm_y = perlin_generate_perm();
int *perlin::perm_z = perlin_generate_perm();

inline float trilinear_interp(float c[2][2][2], float u, float v, float w)
{
	float accum = 0.0f;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				float e0 = float(i) * u + float(1 - i) * (1.0f - u);
				float e1 = float(j) * v + float(1 - j) * (1.0f - v);
				float e2 = float(k) * w + float(1 - k) * (1.0f - w);
				accum += e0 * e1 * e2 * c[i][j][k];
			}
		}
	}
	return accum;
}

float perlin::noise(const vec3 &p) const
{
	float u = p.x() - floorf(p.x());
	float v = p.y() - floorf(p.y());
	float w = p.z() - floorf(p.z());
	u = u * u * (3.0f - 2.0f * u);
	v = v * v * (3.0f - 2.0f * v);
	w = w * w * (3.0f - 2.0f * w);
	int i = floorf(p.x());
	int j = floorf(p.y());
	int k = floorf(p.z());
	float c[2][2][2];
	for (int di = 0; di < 2; di++) {
		for (int dj = 0; dj < 2; dj++) {
			for (int dk = 0; dk < 2; dk++) {
				c[di][dj][dk] = ranfloat[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];
			}
		}
	}
	return trilinear_interp(c, u, v, w);
}
