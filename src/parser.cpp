/*
** EPITECH PROJECT, 2025
** parcer.hpp
** File description:
** parcer.cpp
*/

#include "parser.hpp"
#include <iostream>
#include <libconfig.h++>
#include "triangle.hpp"

bool parser::parseCamera(const std::string &filename, Camera &camera, Lighto &lights, Primitives &primitives)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(filename.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Erreur de lecture du fichier : " << filename << std::endl;
        return false;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Erreur de parsing à " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return false;
    }
    try {
        const auto &cam = cfg.lookup("camera");
        const auto &li = cfg.lookup("lights");
        const auto &prim = cfg.lookup("primitives");
        // Résolution
        const auto &res = cam.lookup("resolution");
        camera.width = res.lookup("width");
        camera.height = res.lookup("height");
        // Position
        const auto &pos = cam.lookup("position");
        camera.x = pos.lookup("x");
        camera.y = pos.lookup("y");
        camera.z = pos.lookup("z");
        // Rotation
        const auto &rot = cam.lookup("rotation");
        camera.x2 = rot.lookup("x");
        camera.y2 = rot.lookup("y");
        camera.z2 = rot.lookup("z");
        // FOV
        camera.fov = cam.lookup("fieldOfView");
        // Spheres
        if (prim.exists("spheres")) {
            const auto &spheres = prim.lookup("spheres");
            for (int i = 0; i < spheres.getLength(); ++i) {
                const auto &sph = spheres[i];
                Sphere sphere;
                sphere.x = sph.lookup("x");
                sphere.y = sph.lookup("y");
                sphere.z = sph.lookup("z");
                sphere.radius = sph.lookup("r");
                const auto &color = sph.lookup("color");
                sphere.color_r = color.lookup("r");
                sphere.color_g = color.lookup("g");
                sphere.color_b = color.lookup("b");
                if (sph.exists("rotation")) {
                    const auto &rotation = sph.lookup("rotation");
                    sphere.rotation_angle = rotation.lookup("rotation_angle");
                    sphere.rotation_axis = rotation.lookup("rotation_axis").c_str();
                } else {
                    sphere.rotation_angle = 0;
                    sphere.rotation_axis = "y";
                }
                primitives.spheres.push_back(sphere);
            }
        }
        //triangle
        if (prim.exists("triangles")) {
            const auto &triangles = prim.lookup("triangles");
            for (int i = 0; i < triangles.getLength(); ++i) {
                const auto &tri = triangles[i];
                Triangle triangle;
                const auto &a = tri.lookup("a");
                triangle.ax = a.lookup("x");
                triangle.ay = a.lookup("y");
                triangle.az = a.lookup("z");
                const auto &b = tri.lookup("b");
                triangle.bx = b.lookup("x");
                triangle.by = b.lookup("y");
                triangle.bz = b.lookup("z");
                const auto &c = tri.lookup("c");
                triangle.cx = c.lookup("x");
                triangle.cy = c.lookup("y");
                triangle.cz = c.lookup("z");
                const auto &color = tri.lookup("color");
                triangle.color_r = color.lookup("r");
                triangle.color_g = color.lookup("g");
                triangle.color_b = color.lookup("b");
                if (tri.exists("rotation")) {
                    const auto &rotation = tri.lookup("rotation");
                    triangle.rotation_angle = rotation.lookup("rotation_angle");
                    triangle.rotation_axis = rotation.lookup("rotation_axis").c_str();
                } else {
                    triangle.rotation_angle = 0;
                    triangle.rotation_axis = "y";
                }
                primitives.triangles.push_back(triangle);
            }
        }
        // Planes
        if (prim.exists("planes")) {
            const auto &planes = prim.lookup("planes");
            for (int i = 0; i < planes.getLength(); ++i) {
                const auto &pln = planes[i];
                Plane plane;
                plane.axis = pln.lookup("axis").c_str();
                plane.position = pln.lookup("position");
                const auto &color = pln.lookup("color");
                plane.color_r = color.lookup("r");
                plane.color_g = color.lookup("g");
                plane.color_b = color.lookup("b");
                if (pln.exists("rotation")) {
                    const auto &rotation = pln.lookup("rotation");
                    plane.rotation_angle = rotation.lookup("rotation_angle");
                    plane.rotation_axis = rotation.lookup("rotation_axis").c_str();
                } else {
                    plane.rotation_angle = 0;
                    plane.rotation_axis = "y";
                }
                primitives.planes.push_back(plane);
            }
        }
        // Cones
        if (prim.exists("cones")) {
            const auto &cones = prim.lookup("cones");
            for (int i = 0; i < cones.getLength(); ++i) {
                const auto &cn = cones[i];
                Cone cone;
                const auto &apex = cn.lookup("apex");
                const auto &direction = cn.lookup("direction");
                const auto &color = cn.lookup("color");
                cone.apex_x = apex.lookup("x");
                cone.apex_y = apex.lookup("y");
                cone.apex_z = apex.lookup("z");
                cone.direction_x = direction.lookup("x");
                cone.direction_y = direction.lookup("y");
                cone.direction_z = direction.lookup("z");
                cone.angle = cn.lookup("angle");
                cone.hight = cn.lookup("height");
                cone.color_r = color.lookup("r");
                cone.color_g = color.lookup("g");
                cone.color_b = color.lookup("b");
                if (cn.exists("rotation")) {
                    const auto &rotation = cn.lookup("rotation");
                    cone.rotation_angle = rotation.lookup("rotation_angle");
                    cone.rotation_axis = rotation.lookup("rotation_axis").c_str();
                } else {
                    cone.rotation_angle = 0;
                    cone.rotation_axis = "y";
                }
                primitives.cone.push_back(cone);
            }
        }
        // Cylinders
        if (prim.exists("cylinders")) {
            const auto &cylinders = prim.lookup("cylinders");
            for (int i = 0; i < cylinders.getLength(); ++i) {
                const auto &cyl = cylinders[i];
                Cylinder cylinder;
                const auto &center = cyl.lookup("center");
                const auto &direction = cyl.lookup("direction");
                const auto &color = cyl.lookup("color");
                cylinder.center_x = center.lookup("x");
                cylinder.center_y = center.lookup("y");
                cylinder.center_z = center.lookup("z");
                cylinder.direction_x = direction.lookup("x");
                cylinder.direction_y = direction.lookup("y");
                cylinder.direction_z = direction.lookup("z");
                cylinder.radius = cyl.lookup("radius");
                cylinder.height = cyl.lookup("height");
                cylinder.color_r = color.lookup("r");
                cylinder.color_g = color.lookup("g");
                cylinder.color_b = color.lookup("b");
                if (cyl.exists("rotation")) {
                    const auto &rotation = cyl.lookup("rotation");
                    cylinder.rotation_angle = rotation.lookup("rotation_angle");
                    cylinder.rotation_axis = rotation.lookup("rotation_axis").c_str();
                } else {
                    cylinder.rotation_angle = 0;
                    cylinder.rotation_axis = "y";
                }
                primitives.cylinders.push_back(cylinder);
            }
        }
        // Lumières
    lights.ambient = li.lookup("ambient");
    lights.diffuse = li.lookup("diffuse");
    if (li.exists("point")) {
        const auto &points = li.lookup("point");
        for (int i = 0; i < points.getLength(); ++i) {
            const auto &p = points[i];
            PointLight pt;
            pt.x = p.lookup("x");
            pt.y = p.lookup("y");
            pt.z = p.lookup("z");
            if (p.exists("intensitypoint")) {
                pt.intensity = p.lookup("intensitypoint");
            }
            lights.points.push_back(pt);
        }
    }
    
    if (li.exists("directional")) {
    const auto &p = li.lookup("directional")[0];
    lights.direct_x = p.lookup("x");
    lights.direct_y = p.lookup("y");
    lights.direct_z = p.lookup("z");
}

    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Champ manquant : " << nfex.getPath() << std::endl;
        return false;
    } catch (const libconfig::SettingTypeException &tpex) {
        std::cerr << "Type de champ incorrect : " << tpex.getPath() << std::endl;
        return false;
    } catch (const std::exception &ex) {
        std::cerr << "Erreur inattendue : " << ex.what() << std::endl;
        return false;
    }
    return true;
}
