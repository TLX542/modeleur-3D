/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** objectsComposite
*/

#include "objects.hpp"
#include <limits>

namespace Objects
{
    Composite::~Composite()
    {
        for (auto& primitive : primitives) {
            delete primitive; // Assuming ownership of
        }
        primitives.clear();
    }

    void Composite::add(IPrimitive* primitive)
    {
        primitives.push_back(primitive);
    }
    
    void Composite::clear()
    {
        primitives.clear();
    }

    std::vector<IPrimitive*> Composite::getPrimitives() const
    {
        return primitives;
    }

    Objects::color Composite::hits(const Ray &ray) const
    {
        double closestDistance = std::numeric_limits<double>::max();
        Objects::color closestColor(0, 0, 0);
        double t;

        for (const auto& primitive : primitives) {
            Objects::color hitColor = primitive->hits(ray, t);
            if (hitColor != Objects::color(0, 0, 0) && t < closestDistance) {
                closestDistance = t;
                closestColor = hitColor;
            }
        }
        return closestColor;
    }

    Objects::color Composite::hits(const Ray &ray, double &t) const
    {
        double closestDistance = std::numeric_limits<double>::max();
        Objects::color closestColor(0, 0, 0);
        double tempT;

        for (const auto& primitive : primitives) {
            Objects::color hitColor = primitive->hits(ray, tempT);
            if (hitColor != Objects::color(0, 0, 0) && tempT < closestDistance) {
                closestDistance = tempT;
                closestColor = hitColor;
            }
        }

        if (closestColor != Objects::color(0, 0, 0))
            t = closestDistance;
            
        return closestColor;
    }

    IPrimitive* Composite::getShapeHit(const Ray &ray) const
    {
        double closestDistance = std::numeric_limits<double>::max();
        IPrimitive* closestPrimitive = nullptr;
        double t;

        for (const auto& primitive : primitives) {
            Objects::color hitColor = primitive->hits(ray, t);
            if (hitColor != Objects::color(0, 0, 0) && t < closestDistance) {
                closestDistance = t;
                closestPrimitive = primitive;
            }
        }
        return closestPrimitive;
    }
}