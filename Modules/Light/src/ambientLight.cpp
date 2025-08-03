/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ambientLight
*/

#include "ambientLight.hpp"

namespace Lights
{
    Math::Vector3D ambientLight::directionFrom(const Math::Point3D &) const{
        return Math::Vector3D(0, 0, 0);
    }

    double ambientLight::intensityAt(const Math::Point3D &) const {
        return intensity;
    }
}