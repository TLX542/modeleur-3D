/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Sphere
*/

#pragma once
#include "color.hpp"
#include "math.hpp"
#include "IPrimitive.hpp"

namespace Objects
{
    class Sphere : public IPrimitive
    {
        color _color;
    public:
        Math::Point3D center;
        double radius;
        Sphere()
            : center(Math::Point3D()), radius(0) {}
        Sphere(const Math::Point3D &center, double radius, color newColor = color(255, 255, 255))
            :  _color(newColor), center(center), radius(radius) {}
        Sphere(const Sphere &sphere)
            : center(sphere.center), radius(sphere.radius) {}
        Sphere &operator=(const Sphere &sphere);
        ~Sphere() = default;
        color hits(const Ray &ray) const;
        color hits(const Ray &ray, double &t) const;
        color getColor() const {return _color;}
        Math::Point3D getOrigin() const override {return center;}
        void applyTransformation(const double &angle, Objects::Axis rotationAxis) override;
        Math::Vector3D getNormal(const Math::Point3D& hitPoint) const override;
    };
}