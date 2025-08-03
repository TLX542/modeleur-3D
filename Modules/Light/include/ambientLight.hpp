/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AmbientLight
*/

#pragma once
#include "ILight.hpp"

namespace Lights {
    class ambientLight : public ILight {
    public:
        double intensity;
        ambientLight(double i) : intensity(i) {}
        Math::Vector3D directionFrom(const Math::Point3D &point) const override;
        double intensityAt(const Math::Point3D &point) const override;
    };
}