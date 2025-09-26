#pragma once

#include <SFML/Graphics.hpp>

class Agent
{
public:
    // Constructor
    Agent(float x, float y);

    // Updates the agent's position based on the elapsed time (dt).
    void update(float dt);

    // Draws the agent to the specified window.
    void draw(sf::RenderWindow &window);

private:
    sf::Vector2f position; // Agent's current location
    sf::Vector2f velocity; // Agent's current speed (in pixels per second)
    sf::CircleShape shape; // Visual representation of the agent
};