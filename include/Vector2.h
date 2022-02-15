#pragma once

#include <math.h>
#include <iostream>

_NAMESPACE_BEGIN
using std::ostream;
using namespace std;
template <class T>
class Vector2 {
  public:
    T x = 0;
    T y = 0;

    Vector2() = default;

    Vector2(T x, T y) {
        this->x = x;
        this->y = y;
    }

    Vector2(const Vector2<T>& other)
        : x(other.x)
        , y(other.y) {}

    ~Vector2() = default;

    T length() {
        return sqrt(x * x + y * y);
    }

    T squaredLength() {
        return x * x + y * y;
    }

    T distanceTo(Vector2<T> p) const {
        return ((*this) - p).length();
    }

    T squaredDistanceTo(const Vector2<T>& p) const {
        return ((*this) - p).squaredLength();
    }

    void normalize() {
        T magSq = x * x + y * y;
        if (magSq > 0.0f) {
            T oneOverMag = 1.0f / sqrt(magSq);
            x *= oneOverMag;
            y *= oneOverMag;
        }
    }

    void swap(Vector2<T>& p) {
        Vector2<T> tmp = p;
        p = *this;
        *this = tmp;
    }

    T maxValue() {
        return max(x, y);
    }

    Vector2<T> operator-(const Vector2<T>& right) const {
        return Vector2<T>(x - right.x, y - right.y);
    }

    Vector2<T> operator-() const {
        return Vector2<T>(-x, -y);
    }

    Vector2<T> operator+(const Vector2<T>& right) const {
        return Vector2<T>(x + right.x, y + right.y);
    }

    Vector2<T>& operator+=(const Vector2<T>& right) const {
        x += right.x;
        y += right.y;
        return *this;
    }

    T operator*(const Vector2<T>& right) const {
        return x * right.x + y * right.y;
    }

    Vector2<T> operator*(const T& right) const {
        return Vector2<T>(x * right, y * right);
    }

    Vector2<T> operator/(const T& a) const {
        return Vector2<T>(x / a, y / a);
    }

    static Vector2<T> slerp(const Vector2<T>& center, Vector2<T> direction, double distance) {
        Vector2<T> coord;
        direction.normalize();
        coord.x = center.x + distance * direction.x;
        coord.y = center.y + distance * direction.y;
        return coord;
    }

    friend ostream& operator<<(ostream& output, const Vector2<T>& value) {
        output.precision(10);
        output << "[" << value.x << ", " << value.y << "]";
        return output;
    }
};
_NAMESPACE_END
