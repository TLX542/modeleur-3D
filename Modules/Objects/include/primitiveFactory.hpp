/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** primitiveFactory
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "IPrimitive.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "cone.hpp"
#include "cylinder.hpp"
#include "triangle.hpp"

class PrimitiveFactory {
public:
    struct Params {
        Math::Point3D position;
        Math::Vector3D direction;
        double radius;
        double height;
        double angle;
        Objects::color color;
        double rotationAngle = 0.0;
        Objects::Axis rotationAxis = Objects::Y_AXIS;
        Objects::Axis axis;
        double planePos;
        
        // New fields for triangle
        Math::Point3D point1;
        Math::Point3D point2;
        Math::Point3D point3;
    };
    static std::unique_ptr<IPrimitive> create(const std::string &type, const Params &params);
private:
    static const std::unordered_map<std::string, std::function<std::unique_ptr<IPrimitive>(const Params&)>> factoryMap;
};
