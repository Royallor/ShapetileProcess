#pragma once

#include <math.h>
#include <iostream>
#include "base.hpp"

_NAMESPACE_BEGIN
using std::ostream;
using namespace std;
template <class T>
class Vector3 {
  public:
    T x = 0;
    T y = 0;
    T z = 0;

    Vector3() = default;

    Vector3(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3(const Vector3<T>& other)
        : x(other.x)
        , y(other.y)
        , z(other.z) {}

    ~Vector3() = default;

    T length() {
        return sqrt(x * x + y * y + z * z);
    }

    T squaredLength() {
        return x * x + y * y + z * z;
    }

    T distanceTo(Vector3<T> p) const {
        return ((*this) - p).length();
    }

    T squaredDistanceTo(const Vector3<T>& p) const {
        return ((*this) - p).squaredLength();
    }

    void normalize() {
        T magSq = x * x + y * y + z * z;
        if (magSq > 0.0f) {
            T oneOverMag = 1.0f / sqrt(magSq);
            x *= oneOverMag;
            y *= oneOverMag;
            z *= oneOverMag;
        }
    }

    Vector3<T> crossProduct(const Vector3<T>& p) {
        return Vector3<T>(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.z);
    }

    Vector3<T> crossProduct3(const Vector3<T>& p) {
        return Vector3<T>(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - p.x * y);
    }

    void swap(Vector3<T>& p) {
        Vector3<T> tmp = p;
        p = *this;
        *this = tmp;
    }

    T maxValue() {
        return max(x, max(y, z));
    }

    Vector3<T> operator-(const Vector3<T>& right) const {
        return Vector3<T>(x - right.x, y - right.y, z - right.z);
    }

    Vector3<T> operator-() const {
        return Vector3<T>(-x, -y, -z);
    }

    Vector3<T> operator+(const Vector3<T>& right) const {
        return Vector3<T>(x + right.x, y + right.y, z + right.z);
    }

    Vector3<T>& operator+=(const Vector3<T>& right) {
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }

    T operator*(const Vector3<T>& right) const {
        return x * right.x + y * right.y + z * right.z;
    }

    Vector3<T> operator*(const T& right) const {
        return Vector3<T>(x * right, y * right, z * right);
    }

    Vector3<T> operator/(const T& a) const {
        return Vector3<T>(x / a, y / a, z / a);
    }

    template <typename anotherT>
    operator Vector3<anotherT>() const {
        return Vector3<anotherT>(x, y, z);
    }

    static Vector3<T> slerp(const Vector3<T>& center, Vector3<T> direction, double distance) {
        Vector3<T> coord;
        direction.normalize();
        coord.x = center.x + distance * direction.x;
        coord.y = center.y + distance * direction.y;
        coord.z = center.z;
        return coord;
    }

    static Vector3<T> slerp3(const Vector3<T>& center, Vector3<T> direction, double distance) {
        Vector3<T> coord;
        direction.normalize();
        coord.x = center.x + distance * direction.x;
        coord.y = center.y + distance * direction.y;
        coord.z = center.z + distance * direction.z;
        return coord;
    }

    friend ostream& operator<<(ostream& output, const Vector3<T>& value) {
        output.precision(10);
        output << "[" << value.x << ", " << value.y << ", " << value.z << "]";
        return output;
    }
};
_NAMESPACE_END
