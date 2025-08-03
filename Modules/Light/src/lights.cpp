/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** lights
*/

#include "lights.hpp"
#include <limits>

namespace Lights
{
    Composite::~Composite()
    {
        for (auto& light : lights) {
            delete light; // Assuming ownership of lights
        }
        lights.clear();
    }

    void Composite::add(ILight* light)
    {
        lights.push_back(light);
    }

    void Composite::clear()
    {
        for (auto& light : lights) {
            delete light;
        }
        lights.clear();
    }

    std::vector<ILight*> Composite::getLights() const
    {
        return lights;
    }
    
    Math::Vector3D Composite::getLightDirection(const Math::Point3D &point) const
    {
        // This is a simplified approach - in a real-world scenario, 
        // you might want to combine directions based on light intensities
        if (lights.empty()) {
            return Math::Vector3D(0, 0, 0);
        }
        
        // Return direction of the first non-ambient light or zero vector
        for (const auto& light : lights) {
            Math::Vector3D dir = light->directionFrom(point);
            if (dir.length() > 0) {
                return dir;
            }
        }
        
        return Math::Vector3D(0, 0, 0);
    }
    
    double Composite::getLightIntensity(const Math::Point3D &point) const
    {
        double totalIntensity = 0.0;
        
        for (const auto& light : lights) {
            totalIntensity += light->intensityAt(point);
        }
        
        // Clamp intensity to a reasonable range if needed
        // totalIntensity = std::min(totalIntensity, 1.0);
        
        return totalIntensity;
    }
}