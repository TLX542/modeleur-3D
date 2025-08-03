/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** lightFactory
*/

#include "lightFactory.hpp"
#include "errors.hpp"

const std::unordered_map<std::string, std::function<std::unique_ptr<Lights::ILight>(const lightFactory::Params&)>> lightFactory::factoryMap = {
    {"ambient", [](const Params &p) {
        return std::make_unique<Lights::ambientLight>(p.intensity);
    }},
    {"directional", [](const Params &p) {
        return std::make_unique<Lights::directionalLight>(p.direction, p.intensity);
    }},
    {"point", [](const Params &p) {
        return std::make_unique<Lights::pointLight>(p.position, p.intensity);
    }}
};

std::unique_ptr<Lights::ILight> lightFactory::create(const std::string &type, const Params &params)
{
    auto it = factoryMap.find(type);
    if (it != factoryMap.end())
        return it->second(params);
    throw Error_factory();
}