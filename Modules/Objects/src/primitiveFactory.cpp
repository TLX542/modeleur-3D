/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** primitiveFactory
*/

#include "primitiveFactory.hpp"
#include "errors.hpp"


const std::unordered_map<std::string, std::function<std::unique_ptr<IPrimitive>(const PrimitiveFactory::Params&)>> PrimitiveFactory::factoryMap = {
    {"sphere", [](const Params &p) {
        return std::make_unique<Objects::Sphere>(p.position, p.radius, p.color);
    }},
    {"plane", [](const Params &p) {
        return std::make_unique<Objects::Plane>(p.axis, p.planePos, p.color);
    }},
    {"cone", [](const Params &p) {
        return std::make_unique<Objects::Cone>(p.position, p.direction, p.angle, p.height, p.color);
    }},
    {"cylinder", [](const Params &p) {
        return std::make_unique<Objects::Cylinder>(p.position, p.direction, p.radius, p.height, p.color);
    }},
    {"triangle", [](const Params &p) {
        return std::unique_ptr<IPrimitive>(new Objects::Triangle(p.point1, p.point2, p.point3, p.color));
    }}
};

std::unique_ptr<IPrimitive> PrimitiveFactory::create(const std::string &type, const Params &params)
{
    auto it = factoryMap.find(type);
    if (it != factoryMap.end())
        return it->second(params);
    throw Error_factory();
}
