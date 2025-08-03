/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cylinder
*/

#include "cylinder.hpp"
#include <cmath>

namespace Objects
{
    Cylinder &Cylinder::operator=(const Cylinder &cylinder)
    {
        if (this != &cylinder)
        {
            center = cylinder.center;
            direction = cylinder.direction;
            radius = cylinder.radius;
            height = cylinder.height;
        }
        return *this;
    }

    color Cylinder::hits(const Ray &ray) const
    {
        double t;
        return hits(ray, t);
    }

    color Cylinder::hits(const Ray &ray, double &t) const
    {
        // Normalize direction vector
        Math::Vector3D dir = direction;
        double dirLen = dir.length();
        if (dirLen > 0)
            dir = dir / dirLen;
        
        // Origin of cylinder is at the center
        Math::Vector3D co = ray.origin - center;
        
        // Project co and ray direction onto the plane perpendicular to cylinder axis
        Math::Vector3D rayDirPerp = ray.direction - dir * ray.direction.dot(dir);
        Math::Vector3D coPerp = co - dir * co.dot(dir);
        
        // Quadratic equation coefficients
        double a = rayDirPerp.dot(rayDirPerp);
        double b = 2.0 * rayDirPerp.dot(coPerp);
        double c = coPerp.dot(coPerp) - radius * radius;
        
        double discriminant = b * b - 4 * a * c;
        
        // No intersection with the infinite cylinder
        if (discriminant < 0 || fabs(a) < 1e-6)
            return color(0, 0, 0);
        
        double sqrtD = sqrt(discriminant);
        double t0 = (-b - sqrtD) / (2 * a);
        double t1 = (-b + sqrtD) / (2 * a);
        
        // Sort t0 and t1
        if (t0 > t1) std::swap(t0, t1);
        
        // Check if intersection points are within height limit
        double tHit = -1;
        double halfHeight = height / 2.0;
        
        // Check t0 first (closest intersection)
        if (t0 > 0) {
            Math::Point3D p0 = ray.origin + ray.direction * t0;
            double h0 = (p0 - center).dot(dir);
            
            if (fabs(h0) <= halfHeight) {
                tHit = t0;
            } else if (t1 > 0) {
                // If t0 is outside bounds, check t1
                Math::Point3D p1 = ray.origin + ray.direction * t1;
                double h1 = (p1 - center).dot(dir);
                
                if (fabs(h1) <= halfHeight) {
                    tHit = t1;
                }
            }
        }
        
        // Check if we hit the cylinder's caps
        Math::Point3D topCenter = center + dir * halfHeight;
        Math::Point3D bottomCenter = center - dir * halfHeight;
        
        double tTop = -1, tBottom = -1;
        double denominator = ray.direction.dot(dir);
        
        // Check if ray is not parallel to caps
        if (fabs(denominator) > 1e-6) {
            // Top cap
            Math::Vector3D diffTop = topCenter - ray.origin;
            tTop = diffTop.dot(dir) / denominator;
            
            // Bottom cap
            Math::Vector3D diffBottom = bottomCenter - ray.origin;
            tBottom = diffBottom.dot(dir) / denominator;
            
            // Check if top cap intersection is valid
            if (tTop > 0) {
                Math::Point3D p = ray.origin + ray.direction * tTop;
                Math::Vector3D v = p - topCenter;
                
                if (v.length() > radius) {
                    tTop = -1;  // Outside the cap
                }
            }
            
            // Check if bottom cap intersection is valid
            if (tBottom > 0) {
                Math::Point3D p = ray.origin + ray.direction * tBottom;
                Math::Vector3D v = p - bottomCenter;
                
                if (v.length() > radius) {
                    tBottom = -1;  // Outside the cap
                }
            }
        }
        
        // Find the closest valid intersection
        if (tTop > 0 && (tHit < 0 || tTop < tHit)) {
            tHit = tTop;
        }
        
        if (tBottom > 0 && (tHit < 0 || tBottom < tHit)) {
            tHit = tBottom;
        }
        
        if (tHit > 0) {
            t = tHit;
            return _color;
        }
        
        return color(0, 0, 0);
    }

    void Objects::Cylinder::applyTransformation(const double &angle, Objects::Axis rotationAxis)
    {
        // Convert angle from degrees to radians
        double radians = angle * M_PI / 180.0;
        
        // Define the pivot point as the center of cylinder
        Math::Point3D pivotPoint = center;
        
        // For a cylinder, we need to rotate the direction vector
        switch (rotationAxis) {
            case Objects::X_AXIS:
                {
                    // Rotate direction vector around X-axis
                    double newDirY = direction.y * cos(radians) - direction.z * sin(radians);
                    double newDirZ = direction.y * sin(radians) + direction.z * cos(radians);
                    direction.y = newDirY;
                    direction.z = newDirZ;
                }
                break;
                
            case Objects::Y_AXIS:
                {
                    // Rotate direction vector around Y-axis
                    double newDirX = direction.x * cos(radians) - direction.z * sin(radians);
                    double newDirZ = direction.x * sin(radians) + direction.z * cos(radians);
                    direction.x = newDirX;
                    direction.z = newDirZ;
                }
                break;
                
            case Objects::Z_AXIS:
                {
                    // Rotate direction vector around Z-axis
                    double newDirX = direction.x * cos(radians) - direction.y * sin(radians);
                    double newDirY = direction.x * sin(radians) + direction.y * cos(radians);
                    direction.x = newDirX;
                    direction.y = newDirY;
                }
                break;
            }
        
        // Normalize the direction vector
        double length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
        if (length > 0) {
            direction.x /= length;
            direction.y /= length;
            direction.z /= length;
        }
    }

    

    Math::Vector3D Cylinder::getNormal(const Math::Point3D& hitPoint) const {
        // Normalize direction vector
        Math::Vector3D dir = direction.normalize();
        
        // Calculate vector from center to hit point
        Math::Vector3D cp = hitPoint - center;
        
        // Check if hit point is on either cap
        double halfHeight = height / 2.0;
        double hitHeight = cp.dot(dir);
        
        // If we hit the top or bottom cap, normal is the cylinder axis direction
        if (fabs(hitHeight - halfHeight) < 1e-6) {
            return dir;
        } else if (fabs(hitHeight + halfHeight) < 1e-6) {
            return -dir;
        }
        
        // Otherwise, normal is perpendicular to the cylinder axis
        // Project hit point onto the cylinder axis
        Math::Point3D axisPoint = center + dir * hitHeight;
        
        // Normal is direction from axis to hit point, normalized
        Math::Vector3D normal = hitPoint - axisPoint;
        return normal.normalize();
    }
}