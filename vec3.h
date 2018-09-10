#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3 {
public:
	vec3() {}
	vec3(float e0, float e1, float e2) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3 &operator +() const { return *this; }
	inline vec3 operator -() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator [](int i) const { return e[i]; }
	inline float &operator [](int i) { return e[i]; }

	inline vec3 &operator +=(const vec3 &v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}
	inline vec3 &operator -=(const vec3 &v) {
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}
	inline vec3 &operator *=(const vec3 &v) {
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}
	inline vec3 &operator /=(const vec3 &v) {
		e[0] /= v.e[0];
		e[1] /= v.e[1];
		e[2] /= v.e[2];
		return *this;
	}
	inline vec3 &operator *=(float t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}
	inline vec3 &operator /=(float t) {
		float k = 1.0f / t;
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
		return *this;
	}

	inline float squared_length() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	inline float length() const {
		return sqrtf(squared_length());
	}
	inline void make_unit_vector();

private:
	float e[3];
};

inline std::istream &operator >>(std::istream &is, vec3 &t)
{
	is >> t[0] >> t[1] >> t[2];
	return is;
}

inline std::ostream &operator <<(std::ostream &os, const vec3 &t)
{
	os << t[0] << " " << t[1] << " " << t[2];
	return os;
}

inline void vec3::make_unit_vector()
{
	float k = 1.0f / length();
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

inline vec3 operator +(const vec3 &a, const vec3 &b)
{
	return vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

inline vec3 operator -(const vec3 &a, const vec3 &b)
{
	return vec3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

inline vec3 operator *(const vec3 &a, const vec3 &b)
{
	return vec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
}

inline vec3 operator /(const vec3 &a, const vec3 &b)
{
	return vec3(a[0] / b[0], a[1] / b[1], a[2] / b[2]);
}

inline vec3 operator *(float t, const vec3 &v)
{
	return vec3(t * v[0], t * v[1], t * v[2]);
}

inline vec3 operator *(const vec3 &v, float t)
{
	return vec3(v[0] * t, v[1] * t, v[2] * t);
}

inline vec3 operator /(const vec3 &v, float t)
{
	float k = 1.0f / t;
	return vec3(v[0] * k, v[1] * k, v[2] * k);
}

inline float dot(const vec3 &a, const vec3 &b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline vec3 cross(const vec3 &a, const vec3 &b)
{
	float e0 = a[1] * b[2] - a[2] * b[1];
	float e1 = a[2] * b[0] - a[0] * b[2];
	float e2 = a[0] * b[1] - a[1] * b[0];
	return vec3(e0, e1, e2);
}

inline vec3 unit_vector(vec3 v)
{
	v.make_unit_vector();
	return v;
}
