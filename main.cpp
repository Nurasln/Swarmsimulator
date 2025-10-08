#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <thread>
#include "Agent.hpp"
#include "Quadtree.hpp"

void update_chunk(std::vector<Agent> *all_agents, QuadTree *qtree, float dt, int start_index, int end_index)
{
    for (int i = start_index; i < end_index; i++)
    {
        Agent &agent = (*all_agents)[i];

        sf::Vector2f pos = agent.getPosition();
        float radius = agent.getPerceptionRadius();
        Rec range(pos.x, pos.y, radius, radius);

        std::vector<Agent *> neighbors;
        qtree->query(range, neighbors);

        agent.update(dt, neighbors);
    }
}

int main()
{

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Swarmsimulator");
    window.setFramerateLimit(60);

    std::vector<Agent> agents;
    const int AGENT_COUNT = 28000;
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

        unsigned int num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0)
        {
            num_threads = 4;
        }

        int chunk_size = agents.size() / num_threads;

        std::vector<std::thread> threads;

        for (unsigned int i = 0; i < num_threads; i++)
        {
            int start = i * chunk_size;
            int end = (i == num_threads - 1) ? agents.size() : (i + 1) * chunk_size;

            threads.emplace_back(update_chunk, &agents, qtree.get(), dt, start, end);
        }

        for (auto &thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
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