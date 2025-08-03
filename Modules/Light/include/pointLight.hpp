/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PointLight
*/

#pragma once
#include "ILight.hpp"

namespace Lights {
    class pointLight : public ILight {
    public:
        Math::Point3D position;
        double intensity;
        
        pointLight(const Math::Point3D &pos, double i)
            : position(pos), intensity(i) {}
        
        Math::Vector3D directionFrom(const Math::Point3D &point) const override;
        double intensityAt(const Math::Point3D &point) const override;
    };
}