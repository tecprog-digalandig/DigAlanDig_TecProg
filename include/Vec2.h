#ifndef Vec2_H
#define Vec2_H

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

    void set(double x, double y) { this->x = x, this->y = y; }

    void rotate(double degrees);
    void rotateRad(double rad);

    double length() const;

    Vec2 normal() const {
        double len = this->length();
        return (len == 0) ? Vec2() : Vec2(*this / len);
    }

    Vec2& normalize();

    double dist(const Vec2& v) const {
        Vec2 d(*this - v);
        return d.length();
    }

    void truncate(double length);

    static double dot(const Vec2& v1, const Vec2& v2);
    static double cross(const Vec2& v1, const Vec2& v2);

    double cross(const Vec2& v2) const { return cross(*this, v2); }
    double dot(const Vec2& v2) const { return dot(*this, v2); }

    Vec2 projection(const Vec2& v2) const {
        return v2 * (dot(*this, v2) / dot(v2, v2));
    }
};

#endif  // Vec2_H
