/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** DirectionalLight
*/

#pragma once
#include "ILight.hpp"

namespace Lights {
    class directionalLight : public ILight {
    public:
        Math::Vector3D direction;
        double intensity;
        directionalLight(const Math::Vector3D &dir, double i)
            : direction(dir.normalize()), intensity(i) {}
        Math::Vector3D directionFrom(const Math::Point3D &point) const override;
        double intensityAt(const Math::Point3D &point) const override;
    };
}