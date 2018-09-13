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
