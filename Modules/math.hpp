/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Math
*/

#pragma once
#include <array>
#include <cmath>
#include <iostream>

namespace Math
{
    class Vector3D
    {
    public:
        double x, y, z;

        Vector3D() : x(0), y(0), z(0) {}
        Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
        Vector3D(const Vector3D &other) : x(other.x), y(other.y), z(other.z) {}
        Vector3D &operator=(const Vector3D &other);
        ~Vector3D() = default;

        Vector3D operator+(const Vector3D &other) const;
        Vector3D operator-(const Vector3D &other) const;
        Vector3D operator*(const Vector3D &other) const;
        Vector3D operator/(const Vector3D &other) const;
        Vector3D operator-() const;

        Vector3D operator+=(const Vector3D &other);
        Vector3D operator-=(const Vector3D &other);
        Vector3D operator*=(const Vector3D &other);
        Vector3D operator/=(const Vector3D &other);

        Vector3D operator*(double scalar) const;
        Vector3D operator/(double scalar) const;
        Vector3D operator/=(double scalar);
        Vector3D operator*=(double scalar);
    
        Vector3D normalize() const;
        double length() const;
        double dot(const Vector3D &other) const;
        Vector3D cross(const Vector3D &other) const;
    };

    class Point3D
    {
    public:
        double x, y, z;

        Point3D() : x(0), y(0), z(0) {}
        Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
        Point3D(const Point3D &other) : x(other.x), y(other.y), z(other.z) {}
        Point3D &operator=(const Point3D &other);
        ~Point3D() = default;

        Point3D operator+(const Vector3D &other) const;
        Point3D operator-(const Vector3D &other) const;
        Vector3D operator+(const Point3D &other) const;
        Vector3D operator-(const Point3D &other) const;
        Point3D operator/(const double) const;
    };

    class Rectangle3D
    {
    public:
        Math::Point3D origin;
        Math::Vector3D bottom_side;
        Math::Vector3D left_side;
        double width;
        double height;

        Rectangle3D() : width(2), height(2) {}

        Rectangle3D(const Math::Point3D &origin,
                    const Math::Vector3D &bottom_side,
                    const Math::Vector3D &left_side)
            : origin(origin), bottom_side(bottom_side), left_side(left_side)
        {
            width = bottom_side.length();
            height = left_side.length();
        }

        Rectangle3D(const Math::Point3D &origin, double width, double height,
                    const Math::Vector3D &direction, const Math::Vector3D &up)
            : origin(origin), width(width), height(height)
        {
            Math::Vector3D right = Math::Vector3D(1, 0, 0);
            if (std::abs(up.dot(direction)) < 0.99)
            {
                right = Math::Vector3D(
                    up.y * direction.z - up.z * direction.y,
                    up.z * direction.x - up.x * direction.z,
                    up.x * direction.y - up.y * direction.x
                );
                double len = right.length();
                if (len > 0)
                    right = right / len;
            }

            bottom_side = right * width;
            left_side = up * height;
        }

        Rectangle3D(const Rectangle3D &other)
            : origin(other.origin), bottom_side(other.bottom_side),
              left_side(other.left_side), width(other.width), height(other.height) {}

        Rectangle3D &operator=(const Rectangle3D &other);
        Math::Point3D pointAt(double u, double v) const;
    };
}
