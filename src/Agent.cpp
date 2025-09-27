#include "Agent.hpp"
#include <cstdlib>
#include <cmath>

// This function calculates the magnitude of a vector
float magnitude(const sf::Vector2f &vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y); // sqrt(x^2 + y^2) (Pythagorean theorem)
}

// This function normalizes a vector (makes its magnitude equal to 1)
sf::Vector2f normalize(const sf::Vector2f &vector)
{
    float mag = magnitude(vector);
    if (mag > 0)
    {
        return vector / mag;
    }
    return vector;
}

// This function limits the magnitude of a vector to a maximum value
void limit(sf::Vector2f &vector, float max)
{
    if (magnitude(vector) > max)
    {
        vector = normalize(vector) * max;
    }
}

// Constructor
Agent::Agent(float x, float y)
{
    // Initialize position, velocity, and shape
    position.x = x;
    position.y = y;

    velocity.x = (rand() % 101 - 50.0f);
    velocity.y = (rand() % 101 - 50.0f);

    shape.setRadius(5.0f);
    shape.setFillColor(sf::Color(
        rand() % 256, // R
        rand() % 256, // G
        rand() % 256  // B
        ));

    // Center the shape's origin
    shape.setOrigin(shape.getRadius(), shape.getRadius());

    maxSpeed = 100.0f;        // Max speed in pixels per second
    maxForce = 10.0f;         // Max steering force
    perceptionRadius = 50.0f; // Radius to consider other agents
}

void Agent::update(float dt, const std::vector<Agent*> &neighbors)
{
    // Boids algorithm implementation
    sf::Vector2f separation(0, 0);
    sf::Vector2f alignment(0, 0);
    sf::Vector2f cohesion(0, 0);

    int perceptionCount = 0;

    for (const auto &otherAgent : neighbors)
    {
        if (this == otherAgent) // Skip self
        {
            continue;
        }

        sf::Vector2f difference = position - otherAgent->getPosition(); // Vector pointing from other agent to this agent
        float distance = magnitude(difference); // Distance between agents

        // Check if within perception radius
        if (distance < perceptionRadius)
        {
            alignment += otherAgent->getVelocity(); 

            cohesion += otherAgent->getPosition();

            if (distance < perceptionRadius / 2) // Stronger separation when closer
            {
                separation += difference / (distance * distance); 
            }
            perceptionCount++;
        }
    }

    if (perceptionCount > 0)
    {
        // Alignment
        alignment /= (float)perceptionCount;
        alignment = normalize(alignment) * maxSpeed;
        alignment -= velocity;
        limit(alignment, maxForce);

        // Cohesion
        cohesion /= (float)perceptionCount;
        cohesion -= position;
        cohesion = normalize(cohesion) * maxSpeed;
        cohesion -= velocity;
        limit(cohesion, maxForce);

        // Separation
        separation /= (float)perceptionCount;
        separation = normalize(separation) * maxSpeed;
        separation -= velocity;
        limit(separation, maxForce);
    }

    velocity += separation * 1.5f;
    velocity += alignment * 1.0f;
    velocity += cohesion * 1.0f;

    // Limit speed
    limit(velocity, maxSpeed);

    // Update position
    position += velocity * dt;

    // Wrap around screen edges
    if (position.x > 800)
        position.x = 0;
    if (position.x < 0)
        position.x = 800;
    if (position.y > 600)
        position.y = 0;
    if (position.y < 0)
        position.y = 600;

    shape.setPosition(position);
}

void Agent::draw(sf::RenderWindow &window)
{
    // Draw the agent's shape to the window
    window.draw(shape);
}