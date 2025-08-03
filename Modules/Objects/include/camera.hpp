/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Camera
*/

#pragma once
#include "math.hpp"
#include "IPrimitive.hpp"

namespace Objects
{
    class Camera
    {
        public:
            Math::Point3D origin;
            Math::Rectangle3D screen;
            double fov;
            double aspectRatio;
            
            Camera() : origin(0, 0, 0), 
                    screen(Math::Rectangle3D(
                        Math::Point3D(-1, -1, -1),
                        Math::Vector3D(2, 0, 0),
                        Math::Vector3D(0, 2, 0))),
                    fov(90.0),
                    aspectRatio(1.0) {}
            
            Camera(const Camera &camera)
                : origin(camera.origin), screen(camera.screen), 
                fov(camera.fov), aspectRatio(camera.aspectRatio) {}
            
            Camera(const Math::Point3D &origin, double fovDegrees, double aspectRatio);
            Camera(const Math::Point3D &origin, double fovDegrees, double aspectRatio,
                const Math::Vector3D &lookDirection, const Math::Vector3D &upVector);
            ~Camera() = default;
            Camera operator=(const Camera &camera);
            Ray ray(double u, double v);
    };
}