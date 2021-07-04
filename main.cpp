#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "hittable.h"
#include "sphere.h"
#include "mat.h"
#include "cam.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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

int main(int argc, char *argv[]) {
	if (argc < 11) return 0;
	char* filename = argv[1];
	// Screen width (nx) and height (ny)
	int nx = (int)strtol(argv[2], &argv[2], 10);
	int ny = (int)strtol(argv[3], &argv[3], 10);
	// Number of samples per pixel
	int ns = (int)strtol(argv[4], &argv[4], 10);
	Vec3 camera_pos, look_at;
	camera_pos.e[0] = strtof(argv[5], &argv[5]);
	camera_pos.e[1] = strtof(argv[6], &argv[6]);
	camera_pos.e[2] = strtof(argv[7], &argv[7]);
	look_at.e[0] = strtof(argv[8], &argv[8]);
	look_at.e[1] = strtof(argv[9], &argv[9]);
	look_at.e[2] = strtof(argv[10], &argv[10]);
	Camera cam(nx, ny, camera_pos, look_at, 3.14159265/4);
	std::unique_ptr<HittableList> hittableList(new HittableList());
	std::shared_ptr<Material> shiny(new Metal(Vec3(1,1,1), 0.0));
	std::shared_ptr<Material> matte(new Lambertian(Vec3(0.5, 0.5, 0.5)));
	std::shared_ptr<Material> velvet(new Metal(Vec3(0.53, 0.14, 0.16), 0.5));
	std::shared_ptr<Material> glass(new Dielectric(Vec3(1.0, 1.0, 1.0), 1.7, 0.0));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(0, 0.5, -2.0), 0.5, shiny)));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(-0.1, 0.5, -3.0), 0.5, glass)));
	hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(Vec3(0, -1000, -1), 1000, matte)));
	for (int i = 0; i < 200; i++) {
		Vec3 pos(drand48() * 6.0 - 3.0, 0.05, drand48() * 6.0 - 6.0);
		if (drand48() < 0.5) {
			std::shared_ptr<Material> mat(new Dielectric(Vec3(drand48(), drand48(), drand48()), 1.5, drand48()/10));
			hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(pos, 0.05, mat)));
		} else {
			std::shared_ptr<Material> mat(new Metal(Vec3(drand48(), drand48(), drand48()), drand48()/10));
			hittableList->list.push_back(std::unique_ptr<Hittable>(new Sphere(pos, 0.05, mat)));
		}
	}
	std::vector<uint8_t> pixels(nx * ny * 3);
	int index = 0;
	// Loop over pixels
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
			pixels[index++] = uint8_t(255.99 * col.r());
			pixels[index++] = uint8_t(255.99 * col.g());
			pixels[index++] = uint8_t(255.99 * col.b());
		}
	}
	stbi_write_png(filename, nx, ny, 3, pixels.data(), nx * 3);
}
