/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Triangle
*/

#pragma once
#include "color.hpp"
#include "math.hpp"
#include "IPrimitive.hpp"

namespace Objects
{
    class Triangle : public IPrimitive
    {
        color _color;
    public:
        Math::Point3D a, b, c;
        Math::Vector3D normal;
        Triangle()
            : _color(255, 255, 255), a(Math::Point3D()), b(Math::Point3D(1, 0, 0)), c(Math::Point3D(0, 1, 0)), normal() {
            computeNormal();
        }
        Triangle(const Math::Point3D &a, const Math::Point3D &b, const Math::Point3D &c, color newColor = color(255, 255, 255))
            : _color(newColor), a(a), b(b), c(c), normal() {
            computeNormal();
        }
        Triangle(const Triangle &triangle)
            : _color(triangle._color),
              a(triangle.a), b(triangle.b), c(triangle.c), normal(triangle.normal) {}
        Triangle &operator=(const Triangle &triangle)
        {
            if (this != &triangle) {
                _color = triangle._color;
                a = triangle.a;
                b = triangle.b;
                c = triangle.c;
                normal = triangle.normal;
            }
            return *this;
        }
        ~Triangle() = default;
        color hits(const Ray &ray) const;
        color hits(const Ray &ray, double &t) const;
        color getColor() const override { return _color; }
        Math::Point3D getOrigin() const override { return a; }
        void applyTransformation(const double &angle, Objects::Axis rotationAxis) override;
        Math::Vector3D getNormal(const Math::Point3D &) const override;
        void setColor(const color& newColor) {
            _color = newColor;
        }
        void computeNormal();
    private:
        void rotatePoint(Math::Point3D &point, const Math::Point3D &pivot, double radians, Objects::Axis axis);
    };
}