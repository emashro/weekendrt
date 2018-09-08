#include <iostream>
#include <float.h>
#include <assert.h>
#include <algorithm>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable.h"
#include "hitablelist.h"
#include "camera.h"

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

class material {
public:
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

class lambertian : public material {
public:
	lambertian(const vec3 &a) : albedo(a) {}
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};

class metal : public material {
public:
	metal(const vec3 &a, float f) : albedo(a), fuzz(std::min(f, 1.0f)) {}
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		attenuation = albedo;
		return dot(scattered.direction(), rec.normal) > 0.0f;
	}
	vec3 albedo;
	float fuzz;
};

float schlick(float cosine, float ref_idx)
{
	float r0 = (1.0f - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1.0f - cosine), 5);
}

class dielectric : public material {
public:
	dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
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
			scattered = ray(rec.p, reflected);
		} else {
			scattered = ray(rec.p, refracted);
		}
		return true;
	}
	float ref_idx;
};

vec3 color(const ray &r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001f, MAXFLOAT, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		} else {
			return vec3(0.0f, 0.0f, 0.0f);
		}
	} else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	hitable *list[5];
	list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, new lambertian(vec3(0.1f, 0.2f, 0.5f)));
	list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, new lambertian(vec3(0.8f, 0.8f, 0.0f)));
	list[2] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f), 0.3f));
	list[3] = new sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, new dielectric(1.5f));
	list[4] = new sphere(vec3(-1.0f, 0.0f, -1.0f), -0.45f, new dielectric(1.5f));
	hitable *world = new hitable_list(list, 5);
	camera cam;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrtf(col[0]), sqrtf(col[1]), sqrtf(col[2]));
			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
