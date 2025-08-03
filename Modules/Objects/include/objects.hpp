/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Objects
*/

#pragma once
#include "camera.hpp"
#include <memory>
#include "primitiveFactory.hpp"

namespace Objects
{
    class Composite
    {
        public:
            Composite() = default;
            ~Composite();
            void add(IPrimitive* primitive);
            void clear();
            std::vector<IPrimitive*> getPrimitives() const;
            Objects::color hits(const Ray &ray) const;
            Objects::color hits(const Ray &ray, double&) const;
            IPrimitive* getShapeHit(const Ray &ray) const;
        private:
            std::vector<IPrimitive*> primitives;
            std::vector<std::shared_ptr<IPrimitive>> children;
    };
}