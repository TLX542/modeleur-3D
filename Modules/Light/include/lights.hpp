/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** lights
*/

#pragma once
#include <vector>
#include <memory>
#include "ILight.hpp"
#include "ambientLight.hpp"
#include "directionalLight.hpp"
#include "pointLight.hpp"

namespace Lights
{
    class Composite
    {
        public:
            Composite() = default;
            ~Composite();
            void add(ILight* light);
            void clear();
            std::vector<ILight*> getLights() const;
            Math::Vector3D getLightDirection(const Math::Point3D &point) const;
            double getLightIntensity(const Math::Point3D &point) const;
        private:
            std::vector<ILight*> lights;
            std::vector<std::shared_ptr<ILight>> children;
    };
}