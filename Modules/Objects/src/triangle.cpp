/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Triangle
*/

#include "triangle.hpp"
#include <cmath>

namespace Objects
{
    void Triangle::computeNormal()
    {
        Math::Vector3D edge1 = b - a;
        Math::Vector3D edge2 = c - a;
        normal = edge1.cross(edge2).normalize();
    }

    color Triangle::hits(const Ray &ray) const
    {
        double t;
        return hits(ray, t);
    }

    color Triangle::hits(const Ray &ray, double &t) const
    {
        const double EPSILON = 1e-6;
        Math::Vector3D edge1 = b - a;
        Math::Vector3D edge2 = c - a;
        Math::Vector3D h = ray.direction.cross(edge2);
        double det = edge1.dot(h);
        if (std::abs(det) < EPSILON)
            return color(0, 0, 0);
        double invDet = 1.0 / det;
        Math::Vector3D s = ray.origin - a;
        double u = invDet * s.dot(h);
        if (u < 0.0 || u > 1.0)
            return color(0, 0, 0);
        Math::Vector3D q = s.cross(edge1);
        double v = invDet * ray.direction.dot(q);
        if (v < 0.0 || u + v > 1.0)
            return color(0, 0, 0);
        t = invDet * edge2.dot(q);
        if (t > EPSILON)
            return _color;
        else
            return color(0, 0, 0);
    }

    void Objects::Triangle::applyTransformation(const double &angle, Objects::Axis rotationAxis) {
        // Convert angle from degrees to radians
        double radians = angle * M_PI / 180.0;
        
        // Define the pivot point as the center of the triangle
        Math::Point3D pivotPoint = Math::Point3D((a.x + b.x + c.x), (a.y + b.y + c.y), (a.z + b.z + c.z)) / 3.0;  // Triangle centroid
        
        // Rotate each vertex of the triangle
        rotatePoint(a, pivotPoint, radians, rotationAxis);
        rotatePoint(b, pivotPoint, radians, rotationAxis);
        rotatePoint(c, pivotPoint, radians, rotationAxis);
        
        // Recompute the normal after rotation
        computeNormal();
    }
    
    void Objects::Triangle::rotatePoint(Math::Point3D &point, const Math::Point3D &pivot, double radians, Objects::Axis axis) {
        // Translate point to origin (relative to pivot)
        Math::Vector3D translated = point - pivot;
        
        // Perform rotation based on the specified axis
        switch (axis) {
            case Objects::X_AXIS: {
                double newY = translated.y * cos(radians) - translated.z * sin(radians);
                double newZ = translated.y * sin(radians) + translated.z * cos(radians);
                translated.y = newY;
                translated.z = newZ;
                break;
            }
            case Objects::Y_AXIS: {
                double newX = translated.x * cos(radians) - translated.z * sin(radians);
                double newZ = translated.x * sin(radians) + translated.z * cos(radians);
                translated.x = newX;
                translated.z = newZ;
                break;
            }
            case Objects::Z_AXIS: {
                double newX = translated.x * cos(radians) - translated.y * sin(radians);
                double newY = translated.x * sin(radians) + translated.y * cos(radians);
                translated.x = newX;
                translated.y = newY;
                break;
            }
        }
        
        // Translate back from origin
        point = pivot + translated;
    }

    Math::Vector3D Objects::Triangle::getNormal(const Math::Point3D &) const
    {
        return normal;
    }
}