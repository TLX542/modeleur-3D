/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone
*/

#include "cone.hpp"
#include <cmath>

namespace Objects
{
    Cone &Cone::operator=(const Cone &cone)
    {
        if (this != &cone)
        {
            apex = cone.apex;
            direction = cone.direction;
            angle = cone.angle;
            height = cone.height;
        }
        return *this;
    }

    color Cone::hits(const Ray &ray) const
    {
        double t;
        return hits(ray, t);
    }

    color Cone::hits(const Ray &ray, double &t) const
    {
        // Normalize direction vector
        Math::Vector3D dir = direction;
        double dirLen = dir.length();
        if (dirLen > 0)
            dir = dir / dirLen;
        
        // Ray origin relative to cone apex
        Math::Vector3D co = ray.origin - apex;
        
        // Compute cone parameters
        double cosTheta = cos(angle * M_PI / 180.0);
        double cos2 = cosTheta * cosTheta;
        
        // Compute the quadratic equation coefficients
        double dot_dir_rayDir = dir.dot(ray.direction);
        double dot_dir_co = dir.dot(co);
        
        double a = dot_dir_rayDir * dot_dir_rayDir - cos2 * ray.direction.dot(ray.direction);
        double b = 2.0 * (dot_dir_rayDir * dot_dir_co - cos2 * ray.direction.dot(co));
        double c = dot_dir_co * dot_dir_co - cos2 * co.dot(co);
        
        double discriminant = b * b - 4 * a * c;
        
        if (discriminant < 0)
            return color(0, 0, 0);
        
        double sqrtD = sqrt(discriminant);
        double t0 = (-b - sqrtD) / (2 * a);
        double t1 = (-b + sqrtD) / (2 * a);
        
        // Sort t0 and t1
        if (t0 > t1) std::swap(t0, t1);
        
        // Check if intersection points are within height limit
        double tHit = -1;
        
        if (t0 > 0) {
            Math::Point3D p0 = ray.origin + ray.direction * t0;
            Math::Vector3D v0 = p0 - apex;
            double h0 = v0.dot(dir);
            
            if (h0 >= 0 && h0 <= height) {
                tHit = t0;
            } else if (t1 > 0) {
                Math::Point3D p1 = ray.origin + ray.direction * t1;
                Math::Vector3D v1 = p1 - apex;
                double h1 = v1.dot(dir);
                
                if (h1 >= 0 && h1 <= height) {
                    tHit = t1;
                }
            }
        }
        
        // Check if we hit the cone's cap
        if (height > 0) {
            Math::Point3D baseCenter = apex + dir * height;
            Math::Vector3D baseNormal = dir;
            
            double denominator = ray.direction.dot(baseNormal);
            if (fabs(denominator) > 1e-6) {
                Math::Vector3D diff = baseCenter - ray.origin;
                double tCap = diff.dot(baseNormal) / denominator;
                
                if (tCap > 0 && (tHit < 0 || tCap < tHit)) {
                    Math::Point3D p = ray.origin + ray.direction * tCap;
                    Math::Vector3D v = p - baseCenter;
                    double radius = height * tan(angle * M_PI / 180.0);
                    
                    if (v.length() <= radius) {
                        tHit = tCap;
                    }
                }
            }
        }
        
        if (tHit > 0) {
            t = tHit;
            return _color;
        }
        
        return color(0, 0, 0);
    }

    void Objects::Cone::applyTransformation(const double &angle, Objects::Axis rotationAxis)
    {
        // Convert angle from degrees to radians
        double radians = angle * M_PI / 180.0;
        
        // Define the pivot point as the apex of the cone
        Math::Point3D pivotPoint = apex;
        
        // For a cone, we need to rotate the direction vector
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
    
    

    Math::Vector3D Cone::getNormal(const Math::Point3D& hitPoint) const
    {
        // Normalize the direction vector for safety
        Math::Vector3D axis = direction.normalize();
        
        // Calculate vector from apex to hit point
        Math::Vector3D v = hitPoint - apex;
        
        // Calculate the height of the hit point along the cone axis
        double heightAlongAxis = v.dot(axis);
        
        // Check if hit point is on base cap (within a small epsilon)
        if (std::abs(heightAlongAxis - height) < 1e-6) {
            // If on base cap, normal is just the axis direction
            return axis;
        }
        
        // Find the point on the axis that is closest to the hit point
        Math::Point3D pointOnAxis = apex + axis * heightAlongAxis;
        
        // Calculate the radial vector (from axis to hit point)
        Math::Vector3D radial = hitPoint - pointOnAxis;
        
        // Calculate the normal by combining the radial direction with the axis direction
        // accounting for the cone's slope
        double slope = std::tan(angle * M_PI / 180.0);
        Math::Vector3D normal = (radial - axis * slope * radial.length()).normalize();
        
        return normal;
    }

}