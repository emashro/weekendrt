#include "hitable.h"

class material;

class sphere : public hitable {
public:
	sphere() {}
	sphere(const vec3 &cen, float r, const material *mat) : center(cen), radius(r), mat_ptr(mat) {}
	virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;

private:
	vec3 center;
	float radius;
	const material *mat_ptr;
};
