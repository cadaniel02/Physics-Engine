#include <random>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "include/FlatVector.h"
#include "include/FlatBody.h"
#include "include/FlatWorld.h"

int main()
{

    const float METERS_TO_PIXELS = 25.0f;
    const float PIXEL_GRAVITY = -9.81f * METERS_TO_PIXELS;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist1k(0, 10);
    std::uniform_real_distribution<float> dist25(0.1f, 1.0f);
    std::uniform_int_distribution<int> dist255(0, 255);
    // Create a window with the given width, height, and title
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Circle Example");
    window.setFramerateLimit(60); // Set the frame rate limit to 60 FPS

    FlatPhysics::FlatVector pos(static_cast<float>(dist1k(rng)), static_cast<float>(dist1k(rng)));

    FlatPhysics::FlatWorld world;

    std::vector<sf::CircleShape> circles;

    bool isMousePressed = false; // Flag to track mouse press state

    //     // Define the static box in the middle of the screen
    // float boxWidth = 1000.0f / METERS_TO_PIXELS; // Width in meters
    // float boxHeight = 100.0f / METERS_TO_PIXELS; // Height in meters
    // float centerX = 1920.0f / 2 / METERS_TO_PIXELS; // Center X in meters
    // float centerY = 1080.0f / 4 / METERS_TO_PIXELS; // Center Y in meters

    // FlatPhysics::FlatVector boxPos(centerX, centerY);
    // float boxMass = 0.0f;
    // std::string errorMsg;
    // auto staticBox = FlatPhysics::CreateBoxBody(boxPos, boxMass, 0, true, boxWidth, boxHeight, errorMsg); // Create the static box body

    // sf::RectangleShape boxShape;
    // boxShape.setSize(sf::Vector2f(boxWidth * METERS_TO_PIXELS, boxHeight * METERS_TO_PIXELS)); // Set size in pixels
    // boxShape.setFillColor(sf::Color::Red); // Color of the static box
    // boxShape.setOrigin(boxWidth * METERS_TO_PIXELS / 2, boxHeight * METERS_TO_PIXELS / 2); // Center the origin
    // boxShape.setPosition(centerX * METERS_TO_PIXELS, 1080 - centerY * METERS_TO_PIXELS); // Set position in pixels

    float containerRadius = 20.0f;
    float centerX = 1920.0f / 2 / METERS_TO_PIXELS; // Center X in meters
    float centerY = 1080.0f / 2 / METERS_TO_PIXELS; // Center Y in meters

    FlatPhysics::FlatVector containerPos(centerX, centerY);
    float containerMass = 0.0f;
    std::string errorMsg;
    auto container = FlatPhysics::CreateCircleBody(containerPos, containerMass, 0, true, containerRadius, errorMsg); // Create the static box body
    world.setConstraint(containerPos, containerRadius);

    sf::CircleShape containerShape{containerRadius * METERS_TO_PIXELS};  // Set size in pixels
    
    containerShape.setFillColor(sf::Color::White); // Color of the static box
    containerShape.setOrigin(containerRadius * METERS_TO_PIXELS, containerRadius * METERS_TO_PIXELS); // Center the origin
    containerShape.setPosition(centerX * METERS_TO_PIXELS, centerY * METERS_TO_PIXELS); // Set position in pixels
    containerShape.setPointCount(128);



    // for (int i = 0; i < 10; ++i)
    // {
    //     float r = static_cast<float>(dist25(rng)); // Generate a new radius for each iteration
    //     float mass = 2.0f;
    //     FlatPhysics::FlatVector pos(static_cast<float>(dist1k(rng)), static_cast<float>(dist1k(rng)));
    //     std::string errorMsg;

    //     // Print out the generated position for debugging
    //     std::cout << "Generated position for body " << i << ": (" << pos.x() << ", " << pos.y() << ")\n";

    //     auto body = FlatPhysics::CreateCircleBody(pos, mass, 0.9f, false, r, errorMsg);
    //     if (!body)
    //     {
    //         std::cerr << "Error creating body: " << errorMsg << std::endl;
    //     }
    //     else {
    //         world.addBody(*body);
    //     }
    // }

    // sf::CircleShape circles[10];

    // for (int i = 0; i < 10; i++)
    // {
    //     const auto& body = world.getBodies()[i]; // Get the body reference
    //     circles[i].setRadius(body.GetRadius() * METERS_TO_PIXELS);
    //     circles[i].setFillColor(sf::Color(dist255(rng), dist255(rng), dist255(rng)));
    //     circles[i].setPosition(body.GetPosition().x() * METERS_TO_PIXELS, 1080 - body.GetPosition().y() * METERS_TO_PIXELS);
    // }

    // Main loop that continues until the window is closed
    sf::Clock clock;
    while (window.isOpen())
    {
        // Create an event object to store window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the window if the close event is triggered
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isMousePressed = true; // Set flag when mouse is pressed
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isMousePressed = false; // Reset flag when mouse is released
                }
            }
        }

        if (isMousePressed) {
            // Get click position
            sf::Vector2i clickPos = sf::Mouse::getPosition(window);
            float posX = static_cast<float>(clickPos.x) / METERS_TO_PIXELS;
            float posY = (1080.0f - static_cast<float>(clickPos.y)) / METERS_TO_PIXELS;

            float r = static_cast<float>(dist25(rng)); // Generate a new radius
            float mass = 2.0f;
            FlatPhysics::FlatVector pos(posX, posY);
            std::string errorMsg;

            // Create a new body at the click position
            auto body = FlatPhysics::CreateCircleBody(pos, mass, 0.9f, false, r, errorMsg);
            if (!body) {
                std::cerr << "Error creating body: " << errorMsg << std::endl;
            } else {
                world.addBody(*body);

                // Create a corresponding circle shape
                std::cout << r << std::endl;
                sf::CircleShape circle;
                circle.setRadius(body->GetRadius() * METERS_TO_PIXELS); // Convert radius to pixels
                circle.setFillColor(sf::Color(dist255(rng), dist255(rng), dist255(rng)));
                circle.setOrigin(body->GetRadius() * METERS_TO_PIXELS, body->GetRadius() * METERS_TO_PIXELS); // Set origin to center
                circle.setPosition(body->GetPosition().x() * METERS_TO_PIXELS, 1080 - body->GetPosition().y() * METERS_TO_PIXELS);

                circles.push_back(circle); // Add the circle to the list
            }
            isMousePressed = false;
        }
    


        float deltaTime = clock.restart().asSeconds();

        world.step(deltaTime);

        for (size_t i = 0; i < circles.size(); i++) {
            const auto& body = world.getBodies()[i];
            circles[i].setPosition(body.GetPosition().x() * METERS_TO_PIXELS, 1080 - body.GetPosition().y() * METERS_TO_PIXELS);
        }

        // Clear the window with a black colordist6
        window.clear(sf::Color::Black);
        // Draw the circle

        window.draw(containerShape);

        for (const auto& circle : circles)
        {
            window.draw(circle);
        }
        // Display the contents of the window
        window.display();
    }

    return 0;
}