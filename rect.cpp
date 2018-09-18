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
	rec.normal = vec3(0.0f, 0.0f, 1.0f);
	return true;
}

bool xz_rect::hit(const ray &r, float t0, float t1, hit_record &rec) const
{
	float t = (k - r.origin().y()) / r.direction().y();
	if (t < t0 || t1 < t) {
		return false;
	}
	float x = r.origin().x() + t * r.direction().x();
	float z = r.origin().z() + t * r.direction().z();
	if (x < x0 || x1 < x || z < z0 || z1 < z) {
		return false;
	}
	rec.u = (x - x0) / (x1 - x0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = vec3(0.0f, 1.0f, 0.0f);
	return true;
}

bool yz_rect::hit(const ray &r, float t0, float t1, hit_record &rec) const
{
	float t = (k - r.origin().x()) / r.direction().x();
	if (t < t0 || t1 < t) {
		return false;
	}
	float y = r.origin().y() + t * r.direction().y();
	float z = r.origin().z() + t * r.direction().z();
	if (y < y0 || y1 < y || z < z0 || z1 < z) {
		return false;
	}
	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = vec3(1.0f, 0.0f, 0.0f);
	return true;
}
