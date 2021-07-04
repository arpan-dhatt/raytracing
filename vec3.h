#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <math.h>
#include <stdlib.h>

class Vec3 {
public:
  Vec3() {
    this->e[0] = 0.0;
    this->e[1] = 0.0;
    this->e[2] = 0.0;
  }

  Vec3(float e0, float e1, float e2) {
    this->e[0] = e0;
    this->e[1] = e1;
    this->e[2] = e2;
  }

  inline float x() const;
  inline float y() const;
  inline float z() const;
  inline float r() const;
  inline float g() const;
  inline float b() const;

  inline const Vec3 &operator+() const;
  inline Vec3 operator-() const;
  inline float operator[](int i) const;
  inline float &operator[](int i);

  inline Vec3 &operator+=(const Vec3 &v2);
  inline Vec3 &operator-=(const Vec3 &v2);
  inline Vec3 &operator*=(const Vec3 &v2);
  inline Vec3 &operator/=(const Vec3 &v2);
  inline Vec3 &operator*=(const float t);
  inline Vec3 &operator/=(const float t);

  inline float mag() const;
  inline float sq_mag() const;
  inline void make_unit();
  inline Vec3 unit();

  float e[3];
};

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2);
inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2);
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2);

inline Vec3 operator*(float t, const Vec3 &v1);
inline Vec3 operator*(const Vec3 &v1, float t);
inline Vec3 operator/(const Vec3 &v1, float t);

inline std::istream &operator>>(std::istream &is, Vec3 &t);
inline std::ostream &operator<<(std::ostream &os, Vec3 &t);

inline float dot(const Vec3 &v1, const Vec3 &v2);
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2);

inline float Vec3::x() const { return e[0]; }

inline float Vec3::y() const { return e[1]; }

inline float Vec3::z() const { return e[2]; }

inline float Vec3::r() const { return e[0]; }

inline float Vec3::g() const { return e[1]; }

inline float Vec3::b() const { return e[2]; }

inline const Vec3 &Vec3::operator+() const { return *this; }

inline Vec3 Vec3::operator-() const { return Vec3(-e[0], -e[1], -e[2]); }

inline float Vec3::operator[](int i) const { return e[i]; }

inline float &Vec3::operator[](int i) { return e[i]; }

inline Vec3 &Vec3::operator+=(const Vec3 &v2) {
  e[0] += v2.e[0];
  e[1] += v2.e[1];
  e[2] += v2.e[2];
  return *this;
}

inline Vec3 &Vec3::operator-=(const Vec3 &v2) {
  e[0] -= v2.e[0];
  e[1] -= v2.e[1];
  e[2] -= v2.e[2];
  return *this;
}

inline Vec3 &Vec3::operator*=(const Vec3 &v2) {
  e[0] *= v2.e[0];
  e[1] *= v2.e[1];
  e[2] *= v2.e[2];
  return *this;
}

inline Vec3 &Vec3::operator/=(const Vec3 &v2) {
  e[0] /= v2.e[0];
  e[1] /= v2.e[1];
  e[2] /= v2.e[2];
  return *this;
}

inline Vec3 &Vec3::operator*=(const float t) {
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

inline Vec3 &Vec3::operator/=(const float t) {
  float k = 1.0 / t;
  e[0] *= k;
  e[1] *= k;
  e[2] *= k;
  return *this;
}

inline float Vec3::mag() const {
  return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}

inline float Vec3::sq_mag() const {
  return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

inline void Vec3::make_unit() { *this /= this->mag(); }

inline Vec3 Vec3::unit() { return *this / this->mag(); }

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(float t, const Vec3 &v1) {
  return Vec3(v1.e[0] * t, v1.e[1] * t, v1.e[2] * t);
}

inline Vec3 operator*(const Vec3 &v1, float t) {
  return Vec3(v1.e[0] * t, v1.e[1] * t, v1.e[2] * t);
}

inline Vec3 operator/(const Vec3 &v1, float t) {
  return Vec3(v1.e[0] / t, v1.e[1] / t, v1.e[2] / t);
}

inline std::istream &operator>>(std::istream &is, Vec3 &t) {
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}

inline std::ostream &operator<<(std::ostream &os, Vec3 &t) {
  os << t.e[0] << " " << t.e[1] << " " << t.e[2];
  return os;
}

inline float dot(const Vec3 &v1, const Vec3 &v2) {
  return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
              v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
              v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline Vec3 random_in_unit_sphere() {
  Vec3 p;
  do {
    p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
  } while (p.sq_mag() >= 1.0);
  return p;
}

inline Vec3 reflect(const Vec3 &v, const Vec3 &N) {
  return v - 2 * dot(v, N) * N;
}

#endif
