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
			get_sphere_uv(rec.normal, rec.u, rec.v);
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

bool sphere::bounding_box(float t0, float t1, aabb &box) const
{
	vec3 radius3(radius, radius, radius);
	box = aabb(center - radius3, center + radius3);
	return true;
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

bool moving_sphere::bounding_box(float t0, float t1, aabb &box) const
{
	vec3 radius3(radius, radius, radius);
	vec3 cen0 = center(t0);
	vec3 cen1 = center(t1);
	aabb box0 = aabb(cen0 - radius3, cen0 + radius3);
	aabb box1 = aabb(cen1 - radius3, cen1 + radius3);
	box = surrounding_box(box0, box1);
	return true;
}
