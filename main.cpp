#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "Agent.hpp"
#include "Quadtree.hpp"

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Swarmsimulator");
    window.setFramerateLimit(60);

    std::vector<Agent> agents;
    const int AGENT_COUNT = 2000;
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

        Rec boundary(400, 300, 400, 300);
        auto qtree = std::make_unique<QuadTree>(boundary, 4);

        for (Agent &agent : agents)
        {
            qtree->insert(&agent);
        }

        for (Agent &agent : agents)
        {
            sf::Vector2f pos = agent.getPosition();
            float radius = agent.getPerceptionRadius();
            Rec range(pos.x, pos.y, radius, radius);

            std::vector<Agent *> neighbors;
            qtree->query(range, neighbors);

            agent.update(dt, neighbors);
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