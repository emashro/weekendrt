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

