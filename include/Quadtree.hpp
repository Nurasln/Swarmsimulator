#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Agent.hpp"

class Rec
{
public:
    float x, y, w, h; // x,y: center of the rectangle; w,h: half-width and half-height

    // Constructor
    Rec(float x = 0, float y = 0, float w = 0, float h = 0)
        : x(x), y(y), w(w), h(h) {}

    // Checks if a point (from an agent) is inside this rectangle.
    bool contains(const Agent *agent) const
    {
        sf::Vector2f pos = agent->getPosition();
        return (pos.x >= x - w &&
                pos.x < x + w &&
                pos.y >= y - h &&
                pos.y < y + h);
    }

    // Checks if this rectangle intersects with another rectangle.
    bool intersects(const Rec &other) const
    {
        return !(other.x - other.w > x + w ||
                 other.x + other.w < x - w ||
                 other.y - other.h > y + h ||
                 other.y + other.h < y - h);
    }
};

class QuadTree
{
private:
    Rec boundary;
    int capacity;
    std::vector<Agent *> agents;
    bool divided = false;

    // sub-quadrants
    QuadTree *northwest = nullptr;
    QuadTree *northeast = nullptr;
    QuadTree *southwest = nullptr;
    QuadTree *southeast = nullptr;

public:
    // Constructor
    QuadTree(Rec boundary, int capacity)
        : boundary(boundary), capacity(capacity) {}

    // Destructor
    ~QuadTree()
    {
        delete northwest;
        delete northeast;
        delete southwest;
        delete southeast;
    }

    // Creates four child nodes that divide this quad into four equal parts.
    void subdivide()
    {
        float x = boundary.x;
        float y = boundary.y;
        float w = boundary.w / 2;
        float h = boundary.h / 2;

        // Create boundaries for the four new children.
        Rec nw(x - w, y - h, w, h);
        Rec ne(x + w, y - h, w, h);
        Rec sw(x - w, y + h, w, h);
        Rec se(x + w, y + h, w, h);

        // Create new QuadTree objects and assign them to the pointers.
        northwest = new QuadTree(nw, capacity);
        northeast = new QuadTree(ne, capacity);
        southwest = new QuadTree(sw, capacity);
        southeast = new QuadTree(se, capacity);

        divided = true;
    }

    // Inserts an agent into the quadtree.
    bool insert(Agent *agent)
    {
        // If the agent is not within the boundary of this quad, do nothing.
        if (!boundary.contains(agent))
        {
            return false;
        }

        // If there is capacity, add the agent to this node.
        if (agents.size() < capacity)
        {
            agents.push_back(agent);
            return true;
        }

        // If capacity is full and not yet divided, subdivide.
        if (!divided)
        {
            subdivide();
        }

        //  After subdividing, pass the agent down to the correct child node.
        if (northeast->insert(agent))
            return true;
        if (northwest->insert(agent))
            return true;
        if (southeast->insert(agent))
            return true;
        if (southwest->insert(agent))
            return true;

        return false;
    }

    // Finds all agents within a given range and adds them to the 'found' vector.
    void query(const Rec &range, std::vector<Agent *> &found) const
    {
        // If the query range does not intersect with this quad's boundary, do not search here.
        if (!boundary.intersects(range))
        {
            return;
        }

        // If it intersects, check the agents in this node.
        for (Agent *agent : agents)
        {
            // Check if the agent's position is within the query range.
            if (range.contains(agent))
            {
                found.push_back(agent);
            }
        }

        // If this quad is divided, recursively query the children.
        if (divided)
        {
            northwest->query(range, found);
            northeast->query(range, found);
            southwest->query(range, found);
            southeast->query(range, found);
        }
    }
};