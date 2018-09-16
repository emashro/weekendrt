#pragma once

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "texture.h"

vec3 random_in_unit_sphere();

vec3 reflect(const vec3 &v, const vec3 &n);

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted);

class material {
public:
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
	virtual vec3 emitted(float u, float v, const vec3 &p) const {
		return vec3(0.0f, 0.0f, 0.0f);
	}
};

class diffuse_light : public material {
public:
	diffuse_light(texture *a) : emit(a) {}
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const { return false; }
	virtual vec3 emitted(float u, float v, const vec3 &p) const {
		return emit->value(u, v, p);
	}

private:
	texture *emit;
};

class lambertian : public material {
public:
	lambertian(const texture *a) : albedo(a) {}
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;

private:
	const texture *albedo;
};

class metal : public material {
public:
	metal(const vec3 &a, float f) : albedo(a), fuzz(std::min(f, 1.0f)) {}
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;

private:
	vec3 albedo;
	float fuzz;
};

float schlick(float cosine, float ref_idx);

class dielectric : public material {
public:
	dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;

private:
	float ref_idx;
};

