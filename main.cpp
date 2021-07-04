#include <cmath>
#include <cstdlib>
#include <iostream>
#include "hittable.h"
#include "sphere.h"
#include "mat.h"

const unsigned int MAX_DEPTH = 10;

Vec3 color(const Ray& r, std::unique_ptr<HittableList>& world, unsigned int depth) {
	Intersection intersect;
	if (world->hit(r, 0.001, MAXFLOAT, intersect)) {
		Ray scatter;
		Vec3 attenuation;
		if (depth < MAX_DEPTH && intersect.mat->scatter(r, intersect, attenuation, scatter)) {
			return attenuation * color(scatter, world, depth+1);
		} else {
			return Vec3(0, 0, 0);
		}
	}
	else {
		// Calculation of background color since nothing hit
		Vec3 unit_direction = r.direction().unit();
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

int main() {
	// Screen width (nx) and height (ny)
	int nx = 800;
	int ny = 500;
	// Number of samples per pixel
	int ns = 100;
	float aspect_ratio = float(nx) / float(ny);
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	Vec3 lower_left_corner(-aspect_ratio, -1.0, -1.0);
	Vec3 horizontal(aspect_ratio * 2, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin;
	std::unique_ptr<HittableList> hittableList(new HittableList());
	std::shared_ptr<Material> shiny(new Metal(Vec3(1,1,1), 0.25));
	std::shared_ptr<Material> matte(new Lambertian(Vec3(0.5, 0.5, 0.5)));
	std::shared_ptr<Material> velvet(new Lambertian(Vec3(0.1, 0.1, 0.1)));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(0, 0, -2.0), 0.5, shiny)));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(0.5, 0, -1.0), 0.2, velvet)));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(0, -100.5, -1), 100, matte)));
	for (int i = 0; i < 10; i++) {
		Vec3 pos = Vec3(drand48() - 0.5, drand48() - 0.5, -drand48()-0.5);
		hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(pos, 0.05, matte)));
	}
	/* Looping where j=0, i=0 is the lower left corner
	 * since writing to the file starts from the top
	 * left of the screen.
	 */
	for (int j = ny-1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			// <u,v> coordinates of the point to get un-normalized direction
			Vec3 col;
			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				Ray r(origin, lower_left_corner + u*horizontal + v*vertical);
				col += color(r, hittableList, 0);
			}
			col /= float(ns);
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
