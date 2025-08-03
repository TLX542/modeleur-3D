/*
** EPITECH PROJECT, 2025
** D6
** File description:
** main.cpp
*/

#include "raytracer.hpp"
#include "parser.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./raytracer <scene_file.cfg>" << std::endl;
        return 84;
    }
    parser pars;
    Lighto ligh;
    Primitives prim;
    Camera cam;
    if (!pars.parseCamera(av[1], cam, ligh, prim)) {
        std::cerr << "Failed to parse camera from file: " << av[1] << std::endl;
        return 84;
    }
    ObjectsCircuit app(cam.width, cam.height);
    Objects::Camera newCam(Math::Point3D(cam.x, cam.y, cam.z), cam.fov, static_cast<double>(cam.width) / cam.height,
        Math::Vector3D(cam.x2, cam.y2, cam.z2), Math::Vector3D(0, 1, 0));
    app.setup(newCam, ligh, prim);
    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;  
        return 84;
    }
    return 0;
}
