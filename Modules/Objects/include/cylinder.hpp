/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cylinder
*/

#pragma once
#include "color.hpp"
#include "math.hpp"
#include "IPrimitive.hpp"

namespace Objects
{
    class Cylinder : public IPrimitive
    {
        color _color;
    public:
        Math::Point3D center;
        Math::Vector3D direction;
        double radius;
        double height;
        
        Cylinder()
            : center(Math::Point3D()), direction(Math::Vector3D(0, 1, 0)), radius(1.0), height(2.0) {}
        Cylinder(const Math::Point3D &center, const Math::Vector3D &direction, double radius, double height, color newColor = color(255, 255, 255))
            : _color(newColor), center(center), direction(direction), radius(radius), height(height) {}
        Cylinder(const Cylinder &cylinder)
            : center(cylinder.center), direction(cylinder.direction), radius(cylinder.radius), height(cylinder.height) {}
        Cylinder &operator=(const Cylinder &cylinder);
        ~Cylinder() = default;
        color hits(const Ray &ray) const;
        color hits(const Ray &ray, double &t) const;
        color getColor() const {return _color;}
        Math::Point3D getOrigin() const override {return center;}
        void applyTransformation(const double &angle, Objects::Axis rotationAxis) override;
        Math::Vector3D getNormal(const Math::Point3D& hitPoint) const override;
    };
}