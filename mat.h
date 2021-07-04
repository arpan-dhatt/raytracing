#ifndef MAT_H
#define MAT_H
#include "hittable.h"
#include "vec3.h"
#include <cstdlib>

class Material {
	public:
		virtual bool scatter(const Ray& incoming, const Intersection& intersect, Vec3& attenuation, Ray& scatter) const = 0;
		virtual ~Material() {}
};

class Lambertian : public Material {
	public:
		Lambertian(const Vec3 alb) : albedo(alb) {}
		bool scatter(const Ray& incoming, const Intersection& intersect, Vec3& attenuation, Ray& scatter) const {
			Vec3 target = intersect.point + intersect.normal + random_in_unit_sphere();
			scatter = Ray(intersect.point, target - intersect.point);
			attenuation = albedo;
			return true;
		}
		~Lambertian() {}
		Vec3 albedo;
};

class Metal : public Material {
	public:
		Metal(const Vec3 alb, const float diff) : albedo(alb), diffusion(diff) {}
		bool scatter(const Ray& incoming, const Intersection& intersect, Vec3& attenuation, Ray& scatter) const {
			Vec3 reflected = reflect(incoming.direction().unit(), intersect.normal);
			scatter = Ray(intersect.point, reflected + diffusion * random_in_unit_sphere());
			attenuation = albedo;
			return (dot(scatter.direction(), intersect.normal) > 0);
			return true;
		}
		~Metal() {}
		Vec3 albedo;
		float diffusion;
};

class Dielectric : public Material {
	public:
		Dielectric(const Vec3 alb, const float ri, const float diff) : albedo(alb), ref_ind(ri), diffusion(diff) {}
		bool scatter(const Ray& incoming, const Intersection& intersect, Vec3& attenuation, Ray& scatter) const {
			Vec3 outward_normal;
			Vec3 reflected = reflect(incoming.direction(), intersect.normal);
			float ni_over_nt;
			attenuation = albedo;
			Vec3 refracted;
			float reflect_prob;
			float cosine;
			if (dot(incoming.direction(), intersect.normal) > 0) {
				outward_normal = -intersect.normal;
				ni_over_nt = ref_ind;
				cosine = ref_ind * dot(incoming.direction(), intersect.normal) / incoming.direction().mag();
			} else {
				outward_normal = intersect.normal;
				ni_over_nt = 1.0/ref_ind;
				cosine = - ref_ind * dot(incoming.direction(), intersect.normal) / incoming.direction().mag();
			}
			if (refract(incoming.direction(), outward_normal, ni_over_nt, refracted)) {
				reflect_prob = schlick(cosine, ref_ind);
			} else {
				scatter = Ray(intersect.point, reflected);
				reflect_prob = 1.0;
			}
			if (drand48() < reflect_prob) {
				scatter = Ray(intersect.point, reflected);
			} else {
				scatter = Ray(intersect.point, refracted);
			}
			scatter.B += random_in_unit_sphere() * diffusion;
			return true;
		}
		~Dielectric() {}
		Vec3 albedo;
		float ref_ind, diffusion;
};

#endif
