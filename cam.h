#ifndef CAM_H
#define CAM_H
#include "ray.h"
#include <cstdlib>
#include <iostream>

class Camera {
	public:
		Camera(float w, float h, const Vec3 pos, const Vec3 lt, float f) {
			width = w; height = h; fov = f;
			position = pos;
			origin = -(lt-pos).unit() + pos;
			look_at = lt;
			Vec3 up = Vec3(0, 1, 0);
			float hori_mag = tan(fov/2) * 2 * w/h;
			float vert_mag = tan(fov/2) * 2;
			horizontal = cross(lt-pos,up).unit() * hori_mag;
			vertical = cross(horizontal, lt-pos).unit() * vert_mag;
			lower_left_corner = pos - vertical / 2 - horizontal / 2;
		}
		Ray get_ray(float u, float v) const;
		int width, height;
		float fov;
		Vec3 position, origin, look_at, vertical, horizontal, lower_left_corner;
};

Ray Camera::get_ray(float u, float v) const {
	u = (u + drand48()) / width;
	v = (v + drand48()) / height;
	return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}

#endif
