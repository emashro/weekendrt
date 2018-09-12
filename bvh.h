#pragma once

#include "hitable.h"

class bvh_node : public hitable {
public:
	bvh_node() {}
	bvh_node(hitable **l, int n, float t0, float t1);
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const;

private:
	hitable *left;
	hitable *right;
	aabb box;
};
