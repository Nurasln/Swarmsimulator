#include <SFML/Graphics.hpp>
#include "Agent.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Swarmsimulator");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Agent myAgent(400, 300);

    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        myAgent.update(dt);
        window.clear();
        myAgent.draw(window);
        window.display();
    }

    return 0;
} 