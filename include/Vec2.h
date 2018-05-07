#ifndef Vec2_H
#define Vec2_H
#include <cmath>
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#define M_1_PI 0.31830988618379067154
#endif

class Vec2 {
  public:
    double x, y;
    Vec2(double x = 0, double y = 0) : x(x), y(y) {}
    Vec2(const Vec2& v) : x(v.x), y(v.y) {}

    Vec2& operator=(const Vec2& v) {
        x = v.x, y = v.y;
        return *this;
    }

    Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
    Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
    Vec2 operator*(const Vec2& v) const { return Vec2(x * v.x, y * v.y); }
    Vec2 operator/(const Vec2& v) const { return Vec2(x / v.x, y / v.y); }
    Vec2& operator+=(const Vec2& v);
    Vec2& operator-=(const Vec2& v);
    Vec2& operator*=(const Vec2& v);
    Vec2& operator/=(const Vec2& v);

    Vec2 operator+(double d) const { return Vec2(x + d, y + d); }
    Vec2 operator-(double d) const { return Vec2(x - d, y - d); }
    Vec2 operator*(double d) const { return Vec2(x * d, y * d); }
    Vec2 operator/(double d) const { return Vec2(x / d, y / d); }
    Vec2& operator+=(double d);
    Vec2& operator-=(double d);
    Vec2& operator*=(double d);
    Vec2& operator/=(double d);

    bool operator<(const Vec2& v) const { return (x < v.x) && (y < v.y); }
    bool operator>(const Vec2& v) const { return (x > v.x) && (y > v.y); }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
        os << "(" << v.x << " , " << v.y << ")";
        return os;
    }

    void Set(double x = 0, double y = 0) { this->x = x, this->y = y; }
    void Set(const Vec2& v) { x = v.x, y = v.y; }

    Vec2 Rotate(double degrees);
    Vec2 RotateRad(double rad);

    double Length() const;

    Vec2 Normal() const {
        double len = this->Length();
        return (len == 0) ? Vec2() : Vec2(*this / len);
    }

    Vec2& Normalize();

    double Angle() const {
        if (x == 0 && y == 0) return 0;
        return atan2(y, x);
    }

    double Dist(const Vec2& v) const {
        Vec2 d(*this - v);
        return d.Length();
    }

    void Truncate(double Length);

    static double Dot(const Vec2& v1, const Vec2& v2);
    static double Cross(const Vec2& v1, const Vec2& v2);

    double Cross(const Vec2& v2) const { return Cross(*this, v2); }
    double Dot(const Vec2& v2) const { return Dot(*this, v2); }

    Vec2 Projection(const Vec2& v2) const {
        return v2 * (Dot(*this, v2) / Dot(v2, v2));
    }
};

#endif  // Vec2_H
