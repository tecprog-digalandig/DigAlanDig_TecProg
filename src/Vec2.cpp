#include "Vec2.h"
#define _USE_MATH_DEFINES
#include <cmath>

Vec2& Vec2::operator+=(const Vec2& v) {
    x += v.x, y += v.y;
    return *this;
}
Vec2& Vec2::operator-=(const Vec2& v) {
    x -= v.x, y -= v.y;
    return *this;
}
Vec2& Vec2::operator*=(const Vec2& v) {
    x *= v.x, y *= v.y;
    return *this;
}
Vec2& Vec2::operator/=(const Vec2& v) {
    x /= v.x, y /= v.y;
    return *this;
}

Vec2& Vec2::operator+=(double d) {
    x += d, y += d;
    return *this;
}
Vec2& Vec2::operator-=(double d) {
    x -= d, y -= d;
    return *this;
}
Vec2& Vec2::operator*=(double d) {
    x *= d, y *= d;
    return *this;
}
Vec2& Vec2::operator/=(double d) {
    x /= d, y /= d;
    return *this;
}

double Vec2::length() const { return std::sqrt(x * x + y * y); }

Vec2 Vec2::rotateRad(double rad) {
    double co = cos(rad);
    double si = sin(rad);
    double tmpX = x * co - y * si;
    double tmpY = x * si + y * co;
    x = tmpX;
    y = tmpY;

    return *this;
}
Vec2 Vec2::rotate(double degrees) { return rotateRad((degrees / 180) * M_PI); }

Vec2& Vec2::normalize() { return *this = normal(); }

void Vec2::truncate(double length) {
    double angle = atan2f(y, x);
    x = length * cos(angle);
    y = length * sin(angle);
}

double Vec2::dot(const Vec2& v1, const Vec2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
double Vec2::cross(const Vec2& v1, const Vec2& v2) {
    return (v1.x * v2.y) - (v1.y * v2.x);
}
