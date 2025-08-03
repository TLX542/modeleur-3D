/*
** EPITECH PROJECT, 2025
** bs-raytracer
** File description:
** Lights interface
*/

#pragma once
#include "math.hpp"

namespace Lights
{
    class ILight
    {
    public:
        virtual ~ILight() = default;
        virtual Math::Vector3D directionFrom(const Math::Point3D &point) const = 0;
        virtual double intensityAt(const Math::Point3D &point) const = 0;
    };
}
