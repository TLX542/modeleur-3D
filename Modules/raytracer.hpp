/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Raytracer
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "objects.hpp"
#include <thread>
#include <mutex>
#include <vector>
#include <fstream>
#include <atomic>
#include "parser.hpp"
#include "lights.hpp"

class ObjectsCircuit 
{
    public:
        ObjectsCircuit(int width, int height);
        ~ObjectsCircuit() = default;
        void run();
        void renderToFile();
        void displayLoop();
        void processEvents(sf::RenderWindow& window, bool& needsRerender);
        sf::Color shade(const Ray &ray);
        void addPrimitives(IPrimitive* shape);
        void setCamera(const Objects::Camera &cam);
        void setLights(const Lighto& lights);
        
        // Multithreading methods
        void renderRows(int startRow, int endRow);
        void render(int&);
        
        // Parsing methods
        void add_primitive_parse_sphere(Primitives &prim);
        void add_primitive_parse_cone(Primitives &prim);
        void add_primitive_parse_plane(Primitives &prim);
        void add_primitive_parse_cylindre(Primitives &prim);
        void add_primitive_parse_triangle(Primitives &prim);
    
        void setup(const Objects::Camera &cam, const Lighto& lights, Primitives &prim);
    private:
        Lighto lights;
        int image_width;
        int image_height;
        Objects::Camera camera;
        Objects::Sphere sphere;
        Objects::Composite shapes;
        
        // Camera movement parameters
        double cameraSpeed;
        double rotationSpeed;
        bool isRenderingForFile;
        std::atomic<bool> shouldStopRendering{false};
        
        // Shared buffer for rendered image
        std::vector<std::vector<sf::Color>> pixelBuffer;
        std::mutex bufferMutex;
        std::atomic<int> completedRows{0};

        double computeLighting(IPrimitive* shapeHit, const Math::Point3D& hitPoint, const Math::Vector3D& normal);
        bool isInShadow(const Math::Point3D& point, const Math::Vector3D& normal,
                const Math::Vector3D& lightDir, double maxDistance, IPrimitive* currentHit);
};

