#include "material.h"

vec3 random_in_unit_sphere()
{
	vec3 p;
	do {
		p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1.0f, 1.0f, 1.0f);
	} while (p.squared_length() >= 1.0f);
	return p;
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
	return v - 2.0f * dot(v, n) * n;
}

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted)
{
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
	if (discriminant > 0.0f) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrtf(discriminant);
		return true;
	} else {
		return false;
	}
}

bool lambertian::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
{
	vec3 target = rec.p + rec.normal + random_in_unit_sphere();
	scattered = ray(rec.p, target - rec.p, r_in.time());
	attenuation = albedo->value(0.0f, 0.0f, rec.p);
	return true;
}

bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
{
	vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time());
	attenuation = albedo;
	return dot(scattered.direction(), rec.normal) > 0.0f;
}

float schlick(float cosine, float ref_idx)
{
	float r0 = (1.0f - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1.0f - cosine), 5);
}

bool dielectric::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
{
	vec3 outward_normal;
	vec3 reflected = reflect(r_in.direction(), rec.normal);
	float ni_over_nt;
	attenuation = vec3(1.0f, 1.0f, 1.0f);
	vec3 refracted;
	float reflect_prob;
	float cosine;
	if (dot(r_in.direction(), rec.normal) > 0.0f) {
		outward_normal = -rec.normal;
		ni_over_nt = ref_idx;
		cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
	} else {
		outward_normal = rec.normal;
		ni_over_nt = 1.0f / ref_idx;
		cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
	}
	if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
		reflect_prob = schlick(cosine, ref_idx);
	} else {
		//scattered = ray(rec.p, reflected);
		reflect_prob = 1.0f;
	}
	if (drand48() < reflect_prob) {
		scattered = ray(rec.p, reflected, r_in.time());
	} else {
		scattered = ray(rec.p, refracted, r_in.time());
	}
	return true;
}
