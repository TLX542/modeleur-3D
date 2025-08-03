/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IPrimitive
*/

#pragma once
#include <vector>

#include "color.hpp"
#include "math.hpp"

namespace Objects {
    enum Axis {
        X_AXIS,
        Y_AXIS, 
        Z_AXIS
    };
}

struct Ray {
    Math::Point3D origin;
    Math::Vector3D direction;
    Math::Vector3D normal; // Added to store the surface normal at hit point
    
    Ray() = default;
    Ray(const Math::Point3D& origin, const Math::Vector3D& direction) 
        : origin(origin), direction(direction) {}
    Ray(const Ray& ray) : origin(ray.origin), direction(ray.direction), normal(ray.normal) {}
    ~Ray() = default;
};

class IPrimitive {
public:
    virtual ~IPrimitive() = default;
    virtual Objects::color hits(const Ray& ray) const = 0;
    virtual Objects::color hits(const Ray& ray, double& t) const = 0;
    virtual Objects::color getColor() const = 0;
    virtual Math::Point3D getOrigin() const = 0;
    virtual void applyTransformation(const double &angle, Objects::Axis rotationAxis) = 0;
    virtual Math::Vector3D getNormal(const Math::Point3D& hitPoint) const = 0;
};
