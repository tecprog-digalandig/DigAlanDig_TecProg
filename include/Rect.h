#ifndef Rect_H
#define Rect_H
#include <iostream>
#include "Vec2.h"

class Rect {
  public:
    Vec2 pos, size;
    double &x, &y, &w, &h;

    Rect(double x = 0, double y = 0, double w = 0, double h = 0)
        : pos(x, y), size(w, h), x(pos.x), y(pos.y), w(size.x), h(size.y) {}
    Rect(const Vec2& _pos, const Vec2& _size)
        : pos(_pos), size(_size), x(pos.x), y(pos.y), w(size.x), h(size.y) {}
    Rect(const Rect& r)
        : pos(r.pos), size(r.size), x(pos.x), y(pos.y), w(size.x), h(size.y) {}

    Rect& operator=(const Rect& r) {
        pos = r.pos, size = r.size;
        return *this;
    }

    Rect operator+(const Vec2& v) const { return Rect(pos + v, size); }
    Rect operator-(const Vec2& v) const { return Rect(pos - v, size); }

    Rect& operator+=(const Vec2& v) {
        pos += v;
        return *this;
    }
    Rect& operator-=(const Vec2& v) { return pos -= v, *this; }

    friend std::ostream& operator<<(std::ostream& os, const Rect& r) {
        os << "Pos: " << r.pos << std::endl << "Size: " << r.size << std::endl;
        return os;
    }

    void Set(double x, double y, double w, double h) {
        this->x = x, this->y = y;
        this->w = w, this->h = h;
    }

    void Set(const Vec2& pos, const Vec2& size) {
        this->pos = pos;
        this->size = size;
    }

    void SetCenter(double x, double y) {
        this->x = x - (w / 2);
        this->y = y - (h / 2);
    }

    void SetCenter(const Vec2& c) { SetCenter(c.x, c.y); }

    Vec2 Center() const { return Vec2(pos + size / 2); }

    bool IsInsideX(double _x) const { return (_x >= x) && (_x < (x + w)); }
    bool IsInsideY(double _y) const { return (_y >= y) && (_y < (y + h)); }
    bool IsInside(const Vec2& v) const { return IsInside(v.x, v.y); }
    bool IsInside(double _x, double _y) const {
        return IsInsideX(_x) && IsInsideY(_y);
    }

    double Dist(const Rect& r) const { return Center().Dist(r.Center()); }
};

#endif  // Rect_H
