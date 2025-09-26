#include "Agent.hpp"

// Constructor
Agent::Agent(float x, float y)
{
    // Initialize position, velocity, and shape
    position.x = x;
    position.y = y;

    velocity.x = 80.0f;
    velocity.y = 60.0f;

    shape.setRadius(10.0f);
    shape.setFillColor(sf::Color::Red);

    // Center the shape's origin
    shape.setOrigin(shape.getRadius(), shape.getRadius());
}

void Agent::update(float dt)
{
    // Update position based on velocity and elapsed time
    position += velocity * dt;
    shape.setPosition(position);
}

void Agent::draw(sf::RenderWindow &window)
{
    // Draw the agent's shape to the window
    window.draw(shape);
}