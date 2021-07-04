#include <cmath>
#include <cstdlib>
#include <iostream>
#include "hittable.h"
#include "sphere.h"
#include "mat.h"
#include "cam.h"

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
	int nx = 1600;
	int ny = 1000;
	// Number of samples per pixel
	int ns = 100;
	Vec3 camera_pos, look_at;
	std::cin >> nx >> ny >> ns >> camera_pos >> look_at;
	Camera cam(nx, ny, camera_pos, look_at, 3.14159265/4);
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	std::unique_ptr<HittableList> hittableList(new HittableList());
	std::shared_ptr<Material> shiny(new Metal(Vec3(1,1,1), 0.0));
	std::shared_ptr<Material> matte(new Lambertian(Vec3(0.5, 0.5, 0.5)));
	std::shared_ptr<Material> velvet(new Metal(Vec3(0.53, 0.14, 0.16), 0.5));
	std::shared_ptr<Material> glass(new Dielectric(Vec3(1.0, 1.0, 1.0), 1.7, 0.0));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(0, 0, -2.0), 0.5, shiny)));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(0.5, 0, -1.0), 0.2, matte)));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(-0.2, -0.3, -1.0), 0.2, glass)));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(0, -100.5, -1), 100, matte)));
	for (int i = 0; i < 25; i++) {
		Vec3 pos(drand48() * 2 - 1, drand48() * 2 - 1, -1 - drand48());
		if (drand48() < 0.5) {
			hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(pos, 0.05, glass)));
		} else {
			hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(pos, 0.05, velvet)));
		}
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
				Ray r = cam.get_ray(i, j);
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
