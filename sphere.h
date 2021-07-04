#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"

class Sphere: public Hittable {
	public:
		Sphere() {}
		Sphere(Vec3 cen, float r) : center(cen), radius(r) {}
		bool hit(const Ray& r, float t_min, float t_max, Intersection& intersect) const;
		~Sphere() {}
		Vec3 center;
		float radius;
};

inline bool Sphere::hit(const Ray& r, float t_min, float t_max, Intersection& intersect) const {
	Vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;
	if (discriminant > 0) {
		float t = (-b - sqrt(discriminant)) / a;
		if (t < t_max && t > t_min) {
			intersect.t = t;
			intersect.point = r.point_at_parameter(t);
			intersect.normal = (intersect.point - center) / radius;
			return true;
		}
		t = (-b + sqrt(discriminant)) / a;
		if (t < t_max && t > t_min) {
			intersect.t = t;
			intersect.point = r.point_at_parameter(t);
			intersect.normal = (intersect.point - center) / radius;
			return true;
		}
	}
	return false;
}


#endif
