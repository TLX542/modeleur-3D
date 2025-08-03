/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Camera
*/

#include "camera.hpp"

namespace Objects
{
    Camera::Camera(const Math::Point3D &origin, double fovDegrees, double aspectRatio)
    : origin(origin), fov(fovDegrees), aspectRatio(aspectRatio)
    {
        double distanceToScreen = 1.0;
        double height = 2.0 * distanceToScreen * tan(fovDegrees * M_PI / 360.0);
        double width = height * aspectRatio;
    
        Math::Point3D screenCenter(0, 0, -distanceToScreen);
        Math::Point3D screenOrigin(
            screenCenter.x - width / 2,
            screenCenter.y - height / 2,
            screenCenter.z
        );
    
        screen = Math::Rectangle3D(
            screenOrigin,
            Math::Vector3D(width, 0, 0),
            Math::Vector3D(0, height, 0)
        );
    }
    
    Camera::Camera(const Math::Point3D &origin, double fovDegrees, double aspectRatio,
               const Math::Vector3D &lookDirection, const Math::Vector3D &upVector)
    : origin(origin), fov(fovDegrees), aspectRatio(aspectRatio)
    {
        Math::Vector3D direction = lookDirection;
        double dirLen = direction.length();
        direction = (dirLen > 0) ? direction / dirLen : Math::Vector3D(0, 0, -1);
    
        Math::Vector3D up = upVector;
        double upLen = up.length();
        up = (upLen > 0) ? up / upLen : Math::Vector3D(0, 1, 0);
    
        double distanceToScreen = 1.0;
        double height = 2.0 * distanceToScreen * tan(fovDegrees * M_PI / 360.0);
        double width = height * aspectRatio;
    
        Math::Point3D screenCenter = Math::Point3D(
            origin.x + direction.x * distanceToScreen,
            origin.y + direction.y * distanceToScreen,
            origin.z + direction.z * distanceToScreen
        );
    
        screen = Math::Rectangle3D(
            screenCenter,
            width,
            height,
            direction,
            up
        );
    
        Math::Vector3D halfWidth = screen.bottom_side / 2;
        Math::Vector3D halfHeight = screen.left_side / 2;
        screen.origin = Math::Point3D(
            screenCenter.x - halfWidth.x - halfHeight.x,
            screenCenter.y - halfWidth.y - halfHeight.y,
            screenCenter.z - halfWidth.z - halfHeight.z
        );
    }
    
    Camera Camera::operator=(const Camera &camera)
    {
        if (this != &camera)
        {
            origin = camera.origin;
            screen = camera.screen;
            fov = camera.fov;
            aspectRatio = camera.aspectRatio;
        }
        return *this;
    }
    
    Ray Camera::ray(double u, double v)
    {
        Math::Point3D point = screen.pointAt(u, v);
        Math::Vector3D direction = point - origin;
    
        double length = direction.length();
        if (length > 0) {
            direction = direction / length;
        }
        return Ray(origin, direction);
    }
}