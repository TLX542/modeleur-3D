/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone
*/

#pragma once
#include "color.hpp"
#include "math.hpp"
#include "IPrimitive.hpp"

namespace Objects
{
    class Cone : public IPrimitive
    {
        color _color;
    public:
        Math::Point3D apex;
        Math::Vector3D direction;
        double angle;
        double height;
        
        Cone()
            : apex(Math::Point3D()), direction(Math::Vector3D(0, -1, 0)), angle(30.0), height(1.0) {}
        Cone(const Math::Point3D &apex, const Math::Vector3D &direction, double angle, double height, color newColor = color(255, 255, 255))
            : _color(newColor), apex(apex), direction(direction), angle(angle), height(height) {}
        Cone(const Cone &cone)
            : apex(cone.apex), direction(cone.direction), angle(cone.angle), height(cone.height) {}
        Cone &operator=(const Cone &cone);
        ~Cone() = default;
        color hits(const Ray &ray) const;
        color hits(const Ray &ray, double &t) const;
        color getColor() const {return _color;}
        Math::Point3D getOrigin() const override {return apex;}
        void applyTransformation(const double &angle, Objects::Axis rotationAxis) override;
        Math::Vector3D getNormal(const Math::Point3D& hitPoint) const override;
    };
}