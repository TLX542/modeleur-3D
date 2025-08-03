/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** lightFactory
*/

#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "lights.hpp"

class lightFactory {
public:
    struct Params {
        Math::Point3D position;
        Math::Vector3D direction;
        double intensity;
    };
    static std::unique_ptr<Lights::ILight> create(const std::string &type, const Params &params);
private:
    static const std::unordered_map<std::string, std::function<std::unique_ptr<Lights::ILight>(const Params&)>> factoryMap;
};