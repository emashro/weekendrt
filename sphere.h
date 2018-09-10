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

class moving_sphere : public hitable {
public:
	moving_sphere() {}
	moving_sphere(const vec3 &cen0, const vec3 &cen1, float t0, float t1, float r, const material *mat) : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(mat) {}
	virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
	vec3 center(float time) const;
	
private:
	vec3 center0, center1;
	float time0, time1;
	float radius;
	const material *mat_ptr;
	
};
