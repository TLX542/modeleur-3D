/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Plane
*/

#pragma once
#include "color.hpp"
#include "IPrimitive.hpp"

namespace Objects
{
    class Plane : public IPrimitive
    {
        color _color;
    public:
        Axis axis;
        double position;
        Math::Point3D point;
        Math::Vector3D normal;
        
        Plane()
            : axis(Y_AXIS), position(0), normal(Math::Vector3D(0, 1, 0)) {}
        Plane(Axis axis, double position, color newColor = color(255, 255, 255));
        Plane(const Plane &plane)
            : _color(plane._color), axis(plane.axis), position(plane.position), normal(plane.normal) {}
        Plane &operator=(const Plane &plane);
        ~Plane() = default;
        color hits(const Ray &ray) const;
        color hits(const Ray &ray, double&) const;
        color getColor() const {return _color;}
        Math::Point3D getOrigin() const override;
        void applyTransformation(const double &angle, Objects::Axis rotationAxis) override;
        Math::Vector3D getNormal(const Math::Point3D&) const override;
    };
}