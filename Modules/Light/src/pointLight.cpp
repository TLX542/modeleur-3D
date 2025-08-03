/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** pointLight
*/

#include "pointLight.hpp"

namespace Lights
{
    Math::Vector3D pointLight::directionFrom(const Math::Point3D &point) const {
        return (position - point).normalize();
    }

    double pointLight::intensityAt(const Math::Point3D &point) const {
        // Get direction vector from point to light
        Math::Vector3D dir = position - point;
        
        // Simple inverse square law attenuation (optional)
        // Minimum value prevents extreme values when very close to the light
        // double attenuation = 1.0 / (1.0 + 0.01 * distance * distance);
        
        // Return constant intensity for now (similar to other lights)
        return intensity;
    }
}