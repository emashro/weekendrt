#include <float.h>
#include "constant_medium.h"

bool constant_medium::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
	bool db = drand48() < 0.00001f;
	db = false;
	hit_record rec1, rec2;
	if (boundary->hit(r, -FLT_MAX, FLT_MAX, rec1)) {
		if (boundary->hit(r, rec1.t + 0.0001f, FLT_MAX, rec2)) {
			if (db) std::cerr << "\nt0 t1 " << rec1.t << " " << rec2.t << "\n";
			if (rec1.t < t_min) {
				rec1.t = t_min;
			}
			if (rec2.t > t_max) {
				rec2.t = t_max;
			}
			if (rec1.t >= rec2.t) {
				return false;
			}
			if (rec1.t < 0) {
				rec1.t = 0;
			}
			float distance_inside_boundary = (rec2.t - rec1.t) * r.direction().length();
			float hit_distance = -(1.0f / density) * log(drand48());
			if (hit_distance < distance_inside_boundary) {
				if (db) std::cerr << "hit_distance = " << hit_distance << "\n";
				rec.t = rec1.t + hit_distance / r.direction().length();
				if (db) std::cerr << "rec.t = " << rec.t << "\n";
				rec.p = r.point_at_parameter(rec.t);
				if (db) std::cerr << "rec.p = "<< rec.p << "\n";
				rec.normal = vec3(1.0f, 0.0f, 0.0f); // arbitrary
				rec.mat_ptr = phase_function;
				return true;
			}
		}
	}
	return false;
}
