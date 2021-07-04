#ifndef HITTABLE_H
#define HITTABLE_H

#include <vector>
#include "ray.h"

struct Intersection {
	float t;
	Vec3 point;
	Vec3 normal;
};

class Hittable {
	public:
		virtual bool hit(const Ray& r, float t_min, float t_max, Intersection& intersect) const = 0;
		virtual ~Hittable() {}
};

class HittableList: public Hittable {
	public:
		HittableList() {}
		bool hit(const Ray& r, float t_min, float t_max, Intersection& intersect) const;
		~HittableList() {}
		std::vector<std::unique_ptr<Hittable>> list;
};

inline bool HittableList::hit(const Ray& r, float t_min, float t_max, Intersection& intersect) const {
	Intersection temp_intersect;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for (int i = 0; i < list.size(); i++) {
		if (list[i]->hit(r, t_min, closest_so_far, temp_intersect)) {
			hit_anything = true;
			closest_so_far = temp_intersect.t;
			intersect = temp_intersect;
		}
	}
	return hit_anything;
}

#endif
