#pragma once

#include "vec3.h"
#include "perlin.h"

class texture {
public:
	virtual vec3 value(float u, float v, const vec3 &p) const = 0;
};

class constant_texture : public texture {
public:
	constant_texture() {}
	constant_texture(const vec3 &c) : color(c) {}
	virtual vec3 value(float u, float v, const vec3 &p) const {
		return color;
	}
private:
	vec3 color;
};

class checker_texture : public texture {
public:
	checker_texture() {}
	checker_texture(texture *t0, texture *t1) : even(t0), odd(t1) {}
	virtual vec3 value(float u, float v, const vec3 &p) const {
		float sines = sinf(10.0f * p.x()) * sinf(10.0f * p.y()) * sin(10.0f * p.z());
		if (sines < 0.0f) {
			return odd->value(u, v, p);
		} else {
			return even->value(u, v, p);
		}
	}
private:
	texture *even;
	texture *odd;
};

class noise_texture : public texture {
public:
	noise_texture() {}
	noise_texture(float sc) : scale(sc) {}
	virtual vec3 value(float u, float v, const vec3 &p) const {
		//return vec3(1.0f, 1.0f, 1.0f) * noise.turb(scale * p);
		return vec3(1.0f, 1.0f, 1.0f) * 0.5f * (1.0f + sin(scale * p.z() + 10.0f * noise.turb(p)));
	}
private:
	perlin noise;
	float scale;
};

class image_texture : public texture {
public:
	image_texture() {}
	image_texture(unsigned char *pixels, int w, int h) : data(pixels), nx(w), ny(h) {}
	virtual vec3 value(float u, float v, const vec3 &p) const;
private:
	unsigned char *data;
	int nx, ny;
};
