#ifndef MAT_H
#define MAT_H
#include "hittable.h"
#include "vec3.h"

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
#endif
