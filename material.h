#pragma once

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

vec3 random_in_unit_sphere();

vec3 reflect(const vec3 &v, const vec3 &n);

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted);

class material {
public:
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

class lambertian : public material {
public:
	lambertian(const vec3 &a) : albedo(a) {}
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;

private:
	vec3 albedo;
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

