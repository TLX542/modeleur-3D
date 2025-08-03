/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Math
*/

#include "math.hpp"
#include "errors.hpp"

namespace Math
{
    constexpr double DEG_TO_RAD = M_PI / 180.0;

    // ----- Vector3D -----

    Vector3D &Vector3D::operator=(const Vector3D &other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    Vector3D Vector3D::operator-() const
    {
        return Vector3D(-x, -y, -z);
    }

    Vector3D Vector3D::operator+(const Vector3D &other) const
    {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D Vector3D::operator-(const Vector3D &other) const
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D Vector3D::operator*(const Vector3D &other) const
    {
        return Vector3D(x * other.x, y * other.y, z * other.z);
    }

    Vector3D Vector3D::operator/(const Vector3D &other) const
    {
        if (other.x == 0 || other.y == 0 || other.z == 0)
            throw Error_Division();
        return Vector3D(x / other.x, y / other.y, z / other.z);
    }

    Vector3D Vector3D::operator+=(const Vector3D &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3D Vector3D::operator-=(const Vector3D &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3D Vector3D::operator*=(const Vector3D &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3D Vector3D::operator/=(const Vector3D &other)
    {
        if (other.x == 0 || other.y == 0 || other.z == 0)
            throw Error_Division();
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vector3D Vector3D::operator*(double scalar) const
    {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D Vector3D::operator/(double scalar) const
    {
        if (scalar == 0)
            throw Error_Division();
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    Vector3D Vector3D::operator/=(double scalar)
    {
        if (scalar == 0)
            throw Error_Division();
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    Vector3D Vector3D::operator*=(double scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    double Vector3D::length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    double Vector3D::dot(const Vector3D &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D Vector3D::normalize() const
    {
        double len = length();
        if (len == 0)
            throw Error_Division();
        return Vector3D(x / len, y / len, z / len);
    }

    Vector3D Vector3D::cross(const Vector3D &other) const
    {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // ----- Point3D -----

    Point3D &Point3D::operator=(const Point3D &other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    Point3D Point3D::operator+(const Vector3D &other) const
    {
        return Point3D(x + other.x, y + other.y, z + other.z);
    }

    Point3D Point3D::operator-(const Vector3D &other) const
    {
        return Point3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D Point3D::operator+(const Point3D &other) const
    {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D Point3D::operator-(const Point3D &other) const
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Point3D Point3D::operator/(const double scalar) const
    {
        if (scalar == 0)
            throw Error_Division();
        return Point3D(x / scalar, y / scalar, z / scalar);
    }

    // ----- Rectangle3D -----

    Rectangle3D &Rectangle3D::operator=(const Rectangle3D &other)
    {
        if (this != &other)
        {
            origin = other.origin;
            bottom_side = other.bottom_side;
            left_side = other.left_side;
            width = other.width;
            height = other.height;
        }
        return *this;
    }

    Point3D Rectangle3D::pointAt(double u, double v) const
    {
        return origin + bottom_side * u + left_side * v;
    }

}
