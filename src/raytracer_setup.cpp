/*
** EPITECH PROJECT, 2025
** D6
** File description:
** add_primitive.cpp
*/

#include "raytracer.hpp"
#include "parser.hpp"
#include <iostream>
#include "primitiveFactory.hpp"
#include "lightFactory.hpp"

void ObjectsCircuit::setup(const Objects::Camera &cam, const Lighto& lights, Primitives &prim)
{
    setCamera(cam);
    setLights(lights);
    add_primitive_parse_sphere(prim);
    add_primitive_parse_cone(prim);
    add_primitive_parse_cylindre(prim);
    add_primitive_parse_plane(prim);
    add_primitive_parse_triangle(prim);
}

void ObjectsCircuit::addPrimitives(IPrimitive* shape)
{
    shapes.add(shape);
}

void ObjectsCircuit::setCamera(const Objects::Camera &cam)
{
    camera = cam;
}

void ObjectsCircuit::setLights(const Lighto& light)
{
    lights = light;
    
    // Clear any existing lights
    lights.composite.clear();
    
    // Create a factory to generate light objects
    lightFactory::Params params;
    
    // Add ambient light
    params.intensity = lights.ambient;
    auto ambientLight = lightFactory::create("ambient", params);
    lights.composite.add(ambientLight.release());
    
    // Add directional light if specified
    if (lights.direct_x != 0 || lights.direct_y != 0 || lights.direct_z != 0) {
        params.direction = Math::Vector3D(lights.direct_x, lights.direct_y, lights.direct_z);
        params.intensity = lights.diffuse;
        auto directionalLight = lightFactory::create("directional", params);
        lights.composite.add(directionalLight.release());
    }
    
    // Add point lights
    for (const auto& point : lights.points) {
        params.position = Math::Point3D(point.x, point.y, point.z);
        params.intensity = lights.diffuse;
        auto pointLight = lightFactory::create("point", params);
        lights.composite.add(pointLight.release());
    }
}

void ObjectsCircuit::add_primitive_parse_sphere(Primitives &prim)
{
    for (const auto &sphere : prim.spheres) {
        PrimitiveFactory::Params p;
        p.position = Math::Point3D(sphere.x, sphere.y, sphere.z);
        p.radius = sphere.radius;
        p.color = Objects::color(sphere.color_r, sphere.color_g, sphere.color_b);
        
        // Add rotation parameters if they exist
        if (sphere.rotation_angle != 0.0) {
            p.rotationAngle = sphere.rotation_angle;
            if (sphere.rotation_axis == "x" || sphere.rotation_axis == "X")
                p.rotationAxis = Objects::X_AXIS;
            else if (sphere.rotation_axis == "y" || sphere.rotation_axis == "Y")
                p.rotationAxis = Objects::Y_AXIS;
            else if (sphere.rotation_axis == "z" || sphere.rotation_axis == "Z")
                p.rotationAxis = Objects::Z_AXIS;
        }
        
        auto primitive = PrimitiveFactory::create("sphere", p);
        primitive->applyTransformation(sphere.rotation_angle, p.rotationAxis);
        addPrimitives(primitive.release());
    }
}

void ObjectsCircuit::add_primitive_parse_cone(Primitives &prim)
{
    for (const auto &cone : prim.cone) {
        PrimitiveFactory::Params p;
        p.position = Math::Point3D(cone.apex_x, cone.apex_y, cone.apex_z);
        p.direction = Math::Vector3D(cone.direction_x, cone.direction_y, cone.direction_z);
        p.angle = cone.angle;
        p.height = cone.hight;
        p.color = Objects::color(cone.color_r, cone.color_g, cone.color_b);
        
        // Add rotation parameters if they exist
        if (cone.rotation_angle != 0.0) {
            p.rotationAngle = cone.rotation_angle;
            if (cone.rotation_axis == "x" || cone.rotation_axis == "X")
                p.rotationAxis = Objects::X_AXIS;
            else if (cone.rotation_axis == "y" || cone.rotation_axis == "Y")
                p.rotationAxis = Objects::Y_AXIS;
            else if (cone.rotation_axis == "z" || cone.rotation_axis == "Z")
                p.rotationAxis = Objects::Z_AXIS;
        }
        auto primitive = PrimitiveFactory::create("cone", p);
        primitive->applyTransformation(cone.rotation_angle, p.rotationAxis);
        addPrimitives(primitive.release());
    }
}

void ObjectsCircuit::add_primitive_parse_plane(Primitives &prim)
{
    for (const auto &plan : prim.planes) {
        PrimitiveFactory::Params p;
        if (plan.axis == "x" || plan.axis == "X")
            p.axis = Objects::Axis::X_AXIS;
        else if (plan.axis == "y" || plan.axis == "Y")
            p.axis = Objects::Axis::Y_AXIS;
        else if (plan.axis == "z" || plan.axis == "Z")
            p.axis = Objects::Axis::Z_AXIS;
        else {
            std::cerr << "Invalid plane axis: " << plan.axis << std::endl;
            continue;
        }

        p.planePos = plan.position;
        p.color = Objects::color(plan.color_r, plan.color_g, plan.color_b);
        
        // Add rotation parameters if they exist
        if (plan.rotation_angle != 0.0) {
            p.rotationAngle = plan.rotation_angle;
            if (plan.rotation_axis == "x" || plan.rotation_axis == "X")
                p.rotationAxis = Objects::X_AXIS;
            else if (plan.rotation_axis == "y" || plan.rotation_axis == "Y")
                p.rotationAxis = Objects::Y_AXIS;
            else if (plan.rotation_axis == "z" || plan.rotation_axis == "Z")
                p.rotationAxis = Objects::Z_AXIS;
        }
        
        auto primitive = PrimitiveFactory::create("plane", p);
        primitive->applyTransformation(plan.rotation_angle, p.rotationAxis);
        addPrimitives(primitive.release());
    }
}

void ObjectsCircuit::add_primitive_parse_cylindre(Primitives &prim)
{
    for (const auto &cylinder : prim.cylinders) {
        PrimitiveFactory::Params p;
        p.position = Math::Point3D(cylinder.center_x, cylinder.center_y, cylinder.center_z);
        p.direction = Math::Vector3D(cylinder.direction_x, cylinder.direction_y, cylinder.direction_z);
        p.radius = cylinder.radius;
        p.height = cylinder.height;
        p.color = Objects::color(cylinder.color_r, cylinder.color_g, cylinder.color_b);
        
        // Add rotation parameters if they exist
        if (cylinder.rotation_angle != 0.0) {
            p.rotationAngle = cylinder.rotation_angle;
            if (cylinder.rotation_axis == "x" || cylinder.rotation_axis == "X")
                p.rotationAxis = Objects::X_AXIS;
            else if (cylinder.rotation_axis == "y" || cylinder.rotation_axis == "Y")
                p.rotationAxis = Objects::Y_AXIS;
            else if (cylinder.rotation_axis == "z" || cylinder.rotation_axis == "Z")
                p.rotationAxis = Objects::Z_AXIS;
        }
        
        auto primitive = PrimitiveFactory::create("cylinder", p);
        primitive->applyTransformation(cylinder.rotation_angle, p.rotationAxis);
        addPrimitives(primitive.release());
    }
}

void ObjectsCircuit::add_primitive_parse_triangle(Primitives &prim)
{
    for (const auto &triangle : prim.triangles) {
        PrimitiveFactory::Params p;
        
        // Set the triangle vertices using float values from the Triangle struct
        p.point1 = Math::Point3D(triangle.ax, triangle.ay, triangle.az);
        p.point2 = Math::Point3D(triangle.bx, triangle.by, triangle.bz);
        p.point3 = Math::Point3D(triangle.cx, triangle.cy, triangle.cz);
        
        // Set the color
        p.color = Objects::color(triangle.color_r, triangle.color_g, triangle.color_b);
        
        // Set rotation parameters if they exist
        if (triangle.rotation_angle != 0.0) {
            p.rotationAngle = triangle.rotation_angle;
            if (triangle.rotation_axis == "x" || triangle.rotation_axis == "X")
                p.rotationAxis = Objects::X_AXIS;
            else if (triangle.rotation_axis == "y" || triangle.rotation_axis == "Y")
                p.rotationAxis = Objects::Y_AXIS;
            else if (triangle.rotation_axis == "z" || triangle.rotation_axis == "Z")
                p.rotationAxis = Objects::Z_AXIS;
        }
        
        // Create the triangle primitive
        auto primitive = PrimitiveFactory::create("triangle", p);
        
        // Apply transformation if rotation is specified
        primitive->applyTransformation(triangle.rotation_angle, p.rotationAxis);
        
        // Add the triangle to the scene
        addPrimitives(primitive.release());
    }
}