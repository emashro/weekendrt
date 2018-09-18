#pragma once

#include "hitable.h"

class xy_rect : public hitable {
public:
	xy_rect() {}
	xy_rect(float x0, float x1, float y0, float y1, float k, material *mat) : x0(x0), x1(x1), y0(y0), y1(y1), k(k), mp(mat) {}
	virtual bool hit(const ray &r, float t0, float t1, hit_record &rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const {
		box = aabb(vec3(x0, y0, k - 0.0001f), vec3(x1, y1, k + 0.0001f));
		return true;
	}

private:
	float x0, x1, y0, y1, k;
	material *mp;
};

class xz_rect : public hitable {
public:
	xz_rect() {}
	xz_rect(float x0, float x1, float z0, float z1, float k, material *mat) : x0(x0), x1(x1), z0(z0), z1(z1), k(k), mp(mat) {}
	virtual bool hit(const ray &r, float t0, float t1, hit_record &rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const {
		box = aabb(vec3(x0, k - 0.0001f, z0), vec3(x1, k + 0.0001f, z1));
		return true;
	}

private:
	float x0, x1, z0, z1, k;
	material *mp;
};

class yz_rect : public hitable {
public:
	yz_rect() {}
	yz_rect(float y0, float y1, float z0, float z1, float k, material *mat) : y0(y0), y1(y1), z0(z0), z1(z1), k(k), mp(mat) {}
	virtual bool hit(const ray &r, float t0, float t1, hit_record &rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const {
		box = aabb(vec3(k - 0.0001f, y0, z0), vec3(k + 0.0001f, y1, z1));
		return true;
	}

private:
	float y0, y1, z0, z1, k;
	material *mp;
};
