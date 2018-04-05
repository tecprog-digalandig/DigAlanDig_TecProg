#ifndef Rect_H
#define Rect_H
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
    Rect& operator-=(const Vec2& v) {
        pos -= v;
        return *this;
    }

    void set(double x, double y, double w, double h) {
        this->x = x, this->y = y;
        this->w = w, this->h = h;
    }

    void set(const Vec2& pos, const Vec2& size) {
        this->pos = pos;
        this->size = size;
    }

    Vec2 center() const { return Vec2(pos + size / 2); }

    bool isInsideX(const Vec2& v) const { return (v.x - pos.x) < size.x; }
    bool isInsideY(const Vec2& v) const { return (v.y - pos.y) < size.y; }
    bool isInside(const Vec2& v) const { return (v - pos) < size; }

    double dist(const Rect& r) const { return center().dist(r.center()); }

  private:
    void bind() {
        this->x = this->pos.x, this->y = this->pos.y;
        this->w = this->size.x, this->h = this->size.y;
    }
};

#endif  // Rect_H
