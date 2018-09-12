#include "aabb.h"

bool aabb::hit(const ray &r, float tmin, float tmax) const
{
	for (int a = 0; a < 3; a++) {
		float inv_d = 1.0f / r.direction()[a];
#if 0
		float t0 = (min()[a] - r.origin()[a]) * inv_d;
		float t1 = (max()[a] - r.origin()[a]) * inv_d;
		if (inv_d < 0.0f) {
			std::swap(t0, t1);
		}
		tmin = t0 > tmin ? t0 : tmin;
		tmax = t1 < tmax ? t1 : tmax;
#else
		float origin = r.origin()[a];
		float t0 = ffmin((min()[a] - origin) * inv_d, (max()[a] - origin) * inv_d);
		float t1 = ffmax((min()[a] - origin) * inv_d, (max()[a] - origin) * inv_d);
		tmin = ffmax(t0, tmin);
		tmax = ffmin(t1, tmax);
#endif
		if (tmax <= tmin) {
			return false;
		}
	}
	return true;
}

aabb surrounding_box(const aabb &box0, const aabb &box1)
{
	float minx = ffmin(box0.min().x(), box1.min().x());
	float miny = ffmin(box0.min().y(), box1.min().y());
	float minz = ffmin(box0.min().z(), box1.min().z());
	float maxx = ffmax(box0.max().x(), box1.max().x());
	float maxy = ffmax(box0.max().y(), box1.max().y());
	float maxz = ffmax(box0.max().z(), box1.max().z());
	return aabb(vec3(minx, miny, minz), vec3(maxx, maxy, maxz));
}
