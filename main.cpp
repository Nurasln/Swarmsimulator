#include <SFML/Graphics.hpp>
#include <vector>
#include "Agent.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Swarmsimulator");
    window.setFramerateLimit(60);

    std::vector<Agent> agents;
    const int AGENT_COUNT = 100;
    for (int i = 0; i < AGENT_COUNT; i++)
    { 
        float startX = rand() % window.getSize().x;
        float startY = rand() % window.getSize().y;
        agents.push_back(Agent(startX, startY));
    }

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

        for (auto &agent : agents)
        {
            agent.update(dt , agents);
        }

        window.clear();

        for (auto &agent : agents)
        {
            agent.draw(window);
        }

        window.display();
    }

    return 0;
}