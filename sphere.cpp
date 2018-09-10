#include "sphere.h"

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction()); // 2倍してない
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c; // b を2倍してないので 4.0f を掛けない
	if (discriminant > 0.0f) {
		float temp = (-b - sqrtf(b * b - a * c)) / a;
		if (t_min < temp && temp < t_max) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrtf(b * b - a * c)) / a;
		if (t_min < temp && temp < t_max) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

vec3 moving_sphere::center(float time) const
{
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
	vec3 cen = center(r.time());
	vec3 oc = r.origin() - cen;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction()); // 2倍してない
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c; // b を2倍してないので 4.0f を掛けない
	if (discriminant > 0.0f) {
		float temp = (-b - sqrtf(b * b - a * c)) / a;
		if (t_min < temp && temp < t_max) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - cen) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrtf(b * b - a * c)) / a;
		if (t_min < temp && temp < t_max) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - cen) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}
