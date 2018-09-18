#pragma once

#include "vec3.h"
#include "ray.h"
#include "aabb.h"

class material;

void get_sphere_uv(const vec3 &p, float &u, float &v);

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
	float u, v;
	const material *mat_ptr;
};

class hitable {
public:
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
	virtual bool bounding_box(float t0, float t1, aabb &box) const = 0;
};

class flip_normals : public hitable {
public:
	flip_normals(hitable *p) : ptr(p) {}
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
		if (ptr->hit(r, t_min, t_max, rec)) {
			rec.normal = -rec.normal;
			return true;
		} else {
			return false;
		}
	}
	virtual bool bounding_box(float t0, float t1, aabb &box) const {
		return ptr->bounding_box(t0, t1, box);
	}

private:
	hitable *ptr;
};

