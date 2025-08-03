/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Raytracer
*/

#include "raytracer.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

/*Initialise la fenêtre SFML, la caméra, la sphère et le buffer d'image*/
ObjectsCircuit::ObjectsCircuit(int width, int height)
    : image_width(width), image_height(height), cameraSpeed(0.15), rotationSpeed(0.03), isRenderingForFile(false)
{
    camera = Objects::Camera(Math::Point3D(0, 0, 0), 90.0, static_cast<double>(width) / height,
        Math::Vector3D(0, 0, -1), Math::Vector3D(0, 1, 0));
    sphere = Objects::Sphere(Math::Point3D(0, 0, -1), 0.5, 
        Objects::color(255, 64, 64));
        
    // Initialize pixel buffer
    pixelBuffer.resize(image_height);
    for (auto& row : pixelBuffer) {
        row.resize(image_width, sf::Color::Black);
    }
}

/*lance le rendu du fichier en parallèle et démarre la boucle d'affichage*/
void ObjectsCircuit::run()
{
    std::thread displayThread(&ObjectsCircuit::displayLoop, this);
    renderToFile();
    displayThread.join();
}

// The function each thread will execute to render a set of rows
void ObjectsCircuit::renderRows(int startRow, int endRow)
{
    for (int j = startRow; j >= endRow; --j) {
        // Check if we should terminate early (for interactive rendering)
        if (shouldStopRendering.load() && !isRenderingForFile) {
            return;
        }

        // Temporary row buffer
        std::vector<sf::Color> rowColors(image_width);
        
        // Render row
        for (int i = 0; i < image_width; ++i) {
            double u = static_cast<double>(i) / (image_width - 1);
            double v = static_cast<double>(j) / (image_height - 1);
            Ray r = camera.ray(u, v);
            rowColors[i] = shade(r);
        }
        
        // Store the completed row in the buffer
        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            // Convert from render coordinates to buffer coordinates
            int bufferRow = image_height - 1 - j;
            if (bufferRow >= 0 && bufferRow < static_cast<int>(pixelBuffer.size())) {
                pixelBuffer[bufferRow] = rowColors;
            }
        }
        
        // Update completed rows counter
        completedRows.fetch_add(1);
    }
}

/*génère le fichier output.ppm en traçant les rayons et écrivant les couleurs*/
void ObjectsCircuit::renderToFile()
{
    // Mark that we're doing a file render
    isRenderingForFile = true;
    
    // Reset the counter and buffer
    completedRows.store(0);
    {
        std::lock_guard<std::mutex> lock(bufferMutex);
        for (auto& row : pixelBuffer) {
            std::fill(row.begin(), row.end(), sf::Color::Black);
        }
    }
    
    // First, render the image using multiple threads
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4; // Fallback
    
    std::cout << "Rendering with " << numThreads << " threads..." << std::endl;
    
    std::vector<std::thread> threads;
    int rowsPerThread = image_height / numThreads;
    
    // Start threads for rendering
    for (unsigned int t = 0; t < numThreads; ++t) {
        int startRow = image_height - 1 - (t * rowsPerThread);
        int endRow = (t == numThreads - 1) ? 0 : image_height - 1 - ((t + 1) * rowsPerThread) + 1;
        
        threads.push_back(std::thread(&ObjectsCircuit::renderRows, this, startRow, endRow));
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Write the rendered image to file
    std::ofstream file("output.ppm");
    if (!file.is_open()) {
        std::cerr << "Failed to open output.ppm" << std::endl;
        return;
    }

    std::cout << "Writing to file..." << std::endl;
    file << "P3\n" << image_width << " " << image_height << "\n255\n";

    // Write from our buffer to the file
    for (const auto& row : pixelBuffer) {
        for (const auto& pixel : row) {
            file << static_cast<int>(pixel.r) << " "
                 << static_cast<int>(pixel.g) << " "
                 << static_cast<int>(pixel.b) << "\n";
        }
    }

    std::cout << "File written successfully." << std::endl;
    isRenderingForFile = false;
}

void ObjectsCircuit::render(int &lastRenderedRow)
{
    // Stop any ongoing interactive rendering
    shouldStopRendering.store(true);

    // Wait a bit for any running threads to terminate
    sf::sleep(sf::milliseconds(50));
    
    // Reset the buffer for a new render
    completedRows.store(0);
    lastRenderedRow = 0;
    
    {
        std::lock_guard<std::mutex> lock(bufferMutex);
        // Clear the buffer
        for (auto& row : pixelBuffer) {
            std::fill(row.begin(), row.end(), sf::Color::Black);
        }
    }
    
    // Allow new threads to run
    shouldStopRendering.store(false);
    
    // Start new rendering threads
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4;
    
    std::vector<std::thread> threads;
    int rowsPerThread = image_height / numThreads;
    
    for (unsigned int t = 0; t < numThreads; ++t) {
        int startRow = image_height - 1 - (t * rowsPerThread);
        int endRow = (t == numThreads - 1) ? 0 : image_height - 1 - ((t + 1) * rowsPerThread) + 1;
        
        threads.push_back(std::thread(&ObjectsCircuit::renderRows, this, startRow, endRow));
    }
    
    // Detach threads to let them run in background
    for (auto& thread : threads) {
        thread.detach();
    }
}

/*boucle window*/
void ObjectsCircuit::displayLoop()
{
    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Super Mega Awesome Raytracer", sf::Style::None);
    sf::Image displayImage;
    sf::Texture displayTexture;
    sf::Sprite displaySprite;
    
    displayImage.create(image_width, image_height, sf::Color::Black);
    
    int lastRenderedRow = 0;
    
    // For interactive rendering
    bool needsRerender = false;
    
    while (window.isOpen()) {
        
        // Check if camera moved and we need to re-render
        if (needsRerender && !isRenderingForFile) {
            render(lastRenderedRow);
            needsRerender = false;
        }
        
        // Don't update the display if we're doing a file render
        if (!isRenderingForFile) {
            // Get current progress
            int currentRows = completedRows.load();
            if (currentRows > lastRenderedRow) {
                // Update display with new rows
                {
                    std::lock_guard<std::mutex> lock(bufferMutex);
                    
                    // Copy from buffer to display image
                    for (int j = 0; j < image_height; ++j) {
                        for (int i = 0; i < image_width; ++i) {
                            displayImage.setPixel(i, j, pixelBuffer[j][i]);
                        }
                    }
                }
                
                lastRenderedRow = currentRows;
                displayTexture.loadFromImage(displayImage);             
            }
        }
        
        // Process events and check for camera movement
        int currentRows = completedRows.load();
        if (!(currentRows > lastRenderedRow)) {
            displaySprite.setTexture(displayTexture, true);
            window.clear();
            window.draw(displaySprite);
            window.display();
            processEvents(window, needsRerender);
        }
        // Small sleep to prevent CPU hogging
        sf::sleep(sf::milliseconds(10));
    }
}

/*gestion event*/
void ObjectsCircuit::processEvents(sf::RenderWindow &window, bool &needsRerender)
{
    sf::Event event;
    
    // Process quit events
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }
    }
    
    // Skip camera movement if we're doing a file render
    if (isRenderingForFile) return;
    
    // Only check camera movement every few frames to avoid overwhelming the renderer
    static int frameCounter = 0;
    frameCounter++;
    if (frameCounter < 5) return;
    frameCounter = 0;
    
    // Get look direction from camera (normalized direction from origin to screen center)
    Math::Point3D screenCenter = camera.screen.origin + 
                                camera.screen.bottom_side / 2 + 
                                camera.screen.left_side / 2;
    Math::Vector3D lookDirection = screenCenter - camera.origin;
    lookDirection = lookDirection.normalize();
    
    // Get the camera's up vector (normalized)
    Math::Vector3D up = camera.screen.left_side.normalize();
    
    // Calculate right vector as cross product of look and up
    Math::Vector3D right = Math::Vector3D(
        lookDirection.y * up.z - lookDirection.z * up.y,
        lookDirection.z * up.x - lookDirection.x * up.z,
        lookDirection.x * up.y - lookDirection.y * up.x
    ).normalize();
    
    // Store the original camera parameters
    Math::Point3D originalPosition = camera.origin;
    Math::Vector3D originalLookDirection = lookDirection;
    Math::Vector3D originalUp = up;
    
    // Check keyboard state for camera movement
    bool moved = false;
    
    // Rotation controls - yaw (left/right)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {  // Rotate right
        // Rotate lookDirection around the up vector
        double cosAngle;
        double sinAngle;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            cosAngle = cos(rotationSpeed);
            sinAngle = sin(rotationSpeed);
        } else {
            cosAngle = cos(-rotationSpeed);
            sinAngle = sin(-rotationSpeed);
        }
        
        Math::Vector3D newLookDirection(
            lookDirection.x * cosAngle + right.x * sinAngle,
            lookDirection.y * cosAngle + right.y * sinAngle,
            lookDirection.z * cosAngle + right.z * sinAngle
        );
        
        lookDirection = newLookDirection.normalize();
        moved = true;
    }
    
    // Rotation controls - pitch (up/down)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) || sf::Keyboard::isKeyPressed(sf::Keyboard::O) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {  // Tilt down
        // Rotate lookDirection around the right vector
        double cosAngle;
        double sinAngle;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            cosAngle = cos(rotationSpeed);
            sinAngle = sin(rotationSpeed);
        } else {
            cosAngle = cos(-rotationSpeed);
            sinAngle = sin(-rotationSpeed);
        }
        
        Math::Vector3D newLookDirection(
            lookDirection.x * cosAngle + up.x * sinAngle,
            lookDirection.y * cosAngle + up.y * sinAngle,
            lookDirection.z * cosAngle + up.z * sinAngle
        );
        
        // Calculate new up vector to maintain orthogonality
        Math::Vector3D newUp = newLookDirection.cross(right).normalize();
        newUp = -newUp; // Flip to maintain "up" direction
        
        lookDirection = newLookDirection.normalize();
        up = newUp;
        moved = true;
    }

    // Original movement controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {  // Forward
        camera.origin = camera.origin + lookDirection * cameraSpeed;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {  // Backward
        camera.origin = camera.origin - lookDirection * cameraSpeed;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  // Strafe left
        camera.origin = camera.origin - right * cameraSpeed;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {  // Strafe right
        camera.origin = camera.origin + right * cameraSpeed;
        moved = true;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {  // Up
        camera.origin = camera.origin + up * cameraSpeed;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {  // Down
        camera.origin = camera.origin - up * cameraSpeed;
        moved = true;
    }

    // If camera position or rotation changed, recreate camera and flag for re-render
    if (moved) {
        // Safely recreate camera with updated position and orientation
        try {
            Objects::Camera newCamera(camera.origin, camera.fov, camera.aspectRatio, 
                                      lookDirection, up);
            camera = newCamera;
            needsRerender = true;
        } catch (std::exception &e) {
            // If we hit an error (like division by zero), restore original parameters
            std::cerr << "Camera update error: " << e.what() << std::endl;
            camera.origin = originalPosition;
            try {
                Objects::Camera newCamera(camera.origin, camera.fov, camera.aspectRatio, 
                                        originalLookDirection, originalUp);
                camera = newCamera;
            } catch (std::exception &e) {
                std::cerr << "Failed to restore camera: " << e.what() << std::endl;
            }
        }
    }
}

double ObjectsCircuit::computeLighting(IPrimitive* shapeHit, const Math::Point3D& hitPoint, const Math::Vector3D& normal)
{
    double totalIntensity = 0.0;

    // Lumières ponctuelles avec intensité individuelle
    for (const auto& pt : lights.points) {
        Math::Vector3D lightDir = Math::Point3D(pt.x, pt.y, pt.z) - hitPoint;
        double distToLight = lightDir.length();
        lightDir = lightDir.normalize();

        if (!isInShadow(hitPoint, normal, lightDir, distToLight, shapeHit)) {
            double diffuse = std::max(0.0, normal.dot(lightDir));
            totalIntensity += pt.intensity * diffuse;
        }
    }

    // Lumière directionnelle
    Math::Vector3D dirLightDir = -Math::Vector3D(lights.direct_x, lights.direct_y, lights.direct_z).normalize();
    if (!isInShadow(hitPoint, normal, dirLightDir, 10000.0, shapeHit)) {
        double diffuse = std::max(0.0, normal.dot(dirLightDir));
        totalIntensity += lights.diffuse * diffuse;
    }

    // Lumière ambiante (ajoutée une seule fois)
    totalIntensity += lights.ambient;

    return std::min(totalIntensity, 1.0);
}


bool ObjectsCircuit::isInShadow(const Math::Point3D& point, const Math::Vector3D& normal,
    const Math::Vector3D& lightDir, double maxDistance, IPrimitive* currentHit)
{
    const double EPSILON = 1e-4;
    Ray shadowRay(point + normal * EPSILON, lightDir);
    double shadowT;

    IPrimitive* shadowHit = shapes.getShapeHit(shadowRay);
    if (shadowHit && shadowHit != currentHit) {
        shadowHit->hits(shadowRay, shadowT);
        if (shadowT > EPSILON && shadowT < maxDistance - EPSILON) {
            return true;
        }
    }
    return false;
}


sf::Color ObjectsCircuit::shade(const Ray &ray)
{
    double t;
    if (!shapes.hits(ray, t))
        return sf::Color::Black;

    IPrimitive* shapeHit = shapes.getShapeHit(ray);
    Math::Point3D hitPoint = ray.origin + ray.direction * t;
    Math::Vector3D normal = shapeHit->getNormal(hitPoint).normalize();
    Objects::color baseColor = shapeHit->getColor();

    double totalIntensity = computeLighting(shapeHit, hitPoint, normal);

    int r = std::min(255, static_cast<int>(totalIntensity * baseColor.r));
    int g = std::min(255, static_cast<int>(totalIntensity * baseColor.g));
    int b = std::min(255, static_cast<int>(totalIntensity * baseColor.b));

    return sf::Color(r, g, b);
}
