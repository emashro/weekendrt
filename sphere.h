#include "hitable.h"

class sphere : public hitable {
public:
	sphere() {}
	sphere(const vec3 &cen, float r) : center(cen), radius(r) {}
	virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
	vec3 center;
	float radius;
};
