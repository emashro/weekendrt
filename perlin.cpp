#include "perlin.h"

static vec3 *perlin_generate()
{
	vec3 *p = new vec3[256];
	for (int i = 0; i < 256; i++) {
		p[i] = unit_vector(vec3(-1.0f + 2.0f * drand48(), -1.0f + 2.0f * drand48(), -1.0f + 2.0f * drand48()));
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

vec3 *perlin::ranvec = perlin_generate();
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

inline float perlin_interp(vec3 c[2][2][2], float u, float v, float w)
{
	float uu = u * u * (3.0f - 2.0f * u);
	float vv = v * v * (3.0f - 2.0f * v);
	float ww = w * w * (3.0f - 2.0f * w);
	float accum = 0.0f;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				vec3 weight_v(u - float(i), v - float(j), w - float(k));
				float e0 = float(i) * uu + float(1 - i) * (1.0f - uu);
				float e1 = float(j) * vv + float(1 - j) * (1.0f - vv);
				float e2 = float(k) * ww + float(1 - k) * (1.0f - ww);
				accum += e0 * e1 * e2 * dot(c[i][j][k], weight_v);
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
	int i = floorf(p.x());
	int j = floorf(p.y());
	int k = floorf(p.z());
	vec3 c[2][2][2];
	for (int di = 0; di < 2; di++) {
		for (int dj = 0; dj < 2; dj++) {
			for (int dk = 0; dk < 2; dk++) {
				c[di][dj][dk] = ranvec[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];
			}
		}
	}
	return perlin_interp(c, u, v, w);
}

float perlin::turb(const vec3 &p, int depth) const
{
	float accum = 0.0f;
	vec3 temp_p = p;
	float weight = 1.0f;
	for (int i = 0; i < depth; i++) {
		accum += weight * noise(temp_p);
		weight *= 0.5f;
		temp_p *= 2.0f;
	}
	return fabsf(accum);
}
