/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** directionalLight
*/

#include "directionalLight.hpp"

namespace Lights
{
    Math::Vector3D directionalLight::directionFrom(const Math::Point3D &) const {
        return -direction;
    }

    double directionalLight::intensityAt(const Math::Point3D &) const {
        return intensity;
    }
}