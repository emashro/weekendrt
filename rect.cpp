#include "rect.h"

bool xy_rect::hit(const ray &r, float t0, float t1, hit_record &rec) const
{
	float t = (k - r.origin().z()) / r.direction().z();
	if (t < t0 || t1 < t) {
		return false;
	}
	float x = r.origin().x() + t * r.direction().x();
	float y = r.origin().y() + t * r.direction().y();
	if (x < x0 || x1 < x || y < y0 || y1 < y) {
		return false;
	}
	rec.u = (x - x0) / (x1 - x0);
	rec.v = (y - y0) / (y1 - y0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = vec3(0.0f, 0.0f, 0.0f);
	return true;
}
