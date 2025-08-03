/*
** EPITECH PROJECT, 2025
** parcer.hpp
** File description:
** parcer.cpp
*/

#pragma once
#include <libconfig.h++>
#include <vector>
#include <string>
#include "lights.hpp"

struct Camera 
{
    float fov;
    int width;
    int height;
    float x;
    float y;
    float z;
    float x2;
    float y2;
    float z2;
};

struct PointLight {
    float x;
    float y;
    float z;
    float intensity = 1.0f;
};

struct Lighto {
    double ambient;
    float diffuse;
    std::vector<PointLight> points;
    float direct_x;
    float direct_y;
    float direct_z;
    Lights::Composite composite;
};


struct Sphere {
    float x, y, z, radius;
    int color_r, color_g, color_b;
    std::string rotation_axis;
    double rotation_angle;
};

struct Plane {
    std::string axis;
    float position;
    int color_r, color_g, color_b;
    std::string rotation_axis;
    double rotation_angle;
};

struct Cone {
    int color_r, color_g, color_b;
    float apex_x;
    float apex_y;
    float apex_z;
    float angle;
    float hight;
    float direction_x;
    float direction_y;
    float direction_z;
    std::string rotation_axis;
    double rotation_angle;
};

struct Cylinder {
    int color_r, color_g, color_b;
    float center_x;
    float center_y;
    float center_z;
    float radius;
    float height;
    float direction_x;
    float direction_y;
    float direction_z;
    std::string rotation_axis;
    double rotation_angle;
};

struct Triangle {
    int color_r, color_g, color_b;
    float ax, ay, az;  // Changed to float to handle decimal values
    float bx, by, bz;  // Changed to float to handle decimal values
    float cx, cy, cz;  // Changed to float to handle decimal values
    std::string rotation_axis;
    double rotation_angle;
};

struct Primitives {
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    std::vector<Cone> cone;
    std::vector<Cylinder> cylinders;
    std::vector<Triangle> triangles;
};

class parser 
{
    public:
        bool parseCamera(const std::string &filename, Camera &camera, Lighto &lights, Primitives &primitives);
};