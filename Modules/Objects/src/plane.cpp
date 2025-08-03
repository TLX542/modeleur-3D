/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Plane
*/

#include "plane.hpp"

namespace Objects
{
    Plane::Plane(Axis axis, double position, color newColor)
        : _color(newColor), axis(axis), position(position)
    {
        // Set normal vector based on axis
        switch (axis) {
            case X_AXIS:
                normal = Math::Vector3D(1, 0, 0);
                break;
            case Y_AXIS:
                normal = Math::Vector3D(0, 1, 0);
                break;
            case Z_AXIS:
                normal = Math::Vector3D(0, 0, 1);
                break;
        }
    }
    
    Plane &Plane::operator=(const Plane &plane)
    {
        if (this != &plane)
        {
            _color = plane._color;
            axis = plane.axis;
            position = plane.position;
            normal = plane.normal;
        }
        return *this;
    }

    Math::Point3D Plane::getOrigin() const
    {
        // Return a point on the plane
        switch (axis) {
            case X_AXIS:
                return Math::Point3D(position, 0, 0);
            case Y_AXIS:
                return Math::Point3D(0, position, 0);
            case Z_AXIS:
                return Math::Point3D(0, 0, position);
        }
        return Math::Point3D(0, 0, 0); // Default fallback
    }

    color Plane::hits(const Ray &ray) const
    {
        double t;
        return hits(ray, t);
    }

    color Plane::hits(const Ray &ray, double &t) const
    {
        double denominator = ray.direction.dot(normal);
        if (fabs(denominator) < 1e-6)
            return color(0, 0, 0);

        // Calculate intersection parameter based on axis
        double originComponent = 0;
        double directionComponent = 1;
        
        switch (axis) {
            case X_AXIS:
                originComponent = ray.origin.x;
                directionComponent = ray.direction.x;
                break;
            case Y_AXIS:
                originComponent = ray.origin.y;
                directionComponent = ray.direction.y;
                break;
            case Z_AXIS:
                originComponent = ray.origin.z;
                directionComponent = ray.direction.z;
                break;
        }
        
        t = (position - originComponent) / directionComponent;
        
        if (t > 0)
            return _color;
        return color(0, 0, 0);
    }

    void Objects::Plane::applyTransformation(const double &angle, Objects::Axis rotationAxis)
    {
        // Convert angle from degrees to radians
        double radians = angle * M_PI / 180.0;
        
        // For planes, we rotate the normal vector based on the rotation axis
        switch (rotationAxis) {
            case Objects::X_AXIS:
                {
                    // Rotate around X-axis (affects Y and Z components)
                    double newY = normal.y * cos(radians) - normal.z * sin(radians);
                    double newZ = normal.y * sin(radians) + normal.z * cos(radians);
                    normal.y = newY;
                    normal.z = newZ;
                }
                break;
                
            case Objects::Y_AXIS:
                {
                    // Rotate around Y-axis (affects X and Z components)
                    double newX = normal.x * cos(radians) - normal.z * sin(radians);
                    double newZ = normal.x * sin(radians) + normal.z * cos(radians);
                    normal.x = newX;
                    normal.z = newZ;
                }
                break;
                
            case Objects::Z_AXIS:
                {
                    // Rotate around Z-axis (affects X and Y components)
                    double newX = normal.x * cos(radians) - normal.y * sin(radians);
                    double newY = normal.x * sin(radians) + normal.y * cos(radians);
                    normal.x = newX;
                    normal.y = newY;
                }
                break;
        }
        
        // Normalize the normal vector
        double length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        if (length > 0) {
            normal.x /= length;
            normal.y /= length;
            normal.z /= length;
        }
    }
    
    

    Math::Vector3D Plane::getNormal(const Math::Point3D&) const {
        // Plane normal is constant regardless of hit point
        return normal.normalize();
    }
}