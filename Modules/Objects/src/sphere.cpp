/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Sphere
*/

#include "sphere.hpp"

namespace Objects
{
    Sphere &Sphere::operator=(const Sphere &sphere)
    {
        if (this != &sphere)
        {
            center = sphere.center;
            radius = sphere.radius;
        }
        return *this;
    }

    color Sphere::hits(const Ray &ray) const
    {
        double t;
        return hits(ray, t);
    }

    color Sphere::hits(const Ray &ray, double &t) const
    {
        Math::Vector3D oc = ray.origin - center;
        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double c = oc.dot(oc) - radius * radius;
        double discriminant = (b * b) - (4 * a * c);

        if (discriminant < 0)
            return color(0, 0, 0);

        double sqrtD = std::sqrt(discriminant);
        double t0 = (-b - sqrtD) / (2 * a);
        double t1 = (-b + sqrtD) / (2 * a);

        if (t0 > 0) {
            t = t0;
            return _color;
        } else if (t1 > 0) {
            t = t1;
            return _color;
        }
        return color(0, 0, 0);
    }

    void Objects::Sphere::applyTransformation(const double &, Objects::Axis rotationAxis)
    {
        // Convert angle to radians if needed
        // double angleInRadians = angle * M_PI / 180.0;
        
        // Apply rotation based on axis
        switch (rotationAxis) {
            case Objects::X_AXIS:
                // Rotation around X axis
                // Implementation would affect texture mapping
                break;
                
            case Objects::Y_AXIS:
                // Rotation around Y axis
                // Implementation would affect texture mapping
                break;
                
            case Objects::Z_AXIS:
                // Rotation around Z axis
                // Implementation would affect texture mapping
                break;
        }
    }
    

    
    

    Math::Vector3D Sphere::getNormal(const Math::Point3D& hitPoint) const {
        // Normal is the normalized vector from center to hit point
        Math::Vector3D normal = hitPoint - center;
        return normal.normalize();
    }
}