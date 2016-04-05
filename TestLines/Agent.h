#pragma once

#include "Graph.h"
#include "Solver.h"
#include "sfwl.h"
#include "Rigidbody.h"


struct Agent;

struct Seek
{
    unsigned current;
    Solver<Vector2> *solver;
    Graph<Vector2>  *graph;
    std::vector<Vector2> waypoints;

    // Randomly select new target position if too close.
    // Otherwise, addForce in direction of target.
    void update(Agent &a);
};

struct Agent
{
    Vector2 position;
    Rigidbody rigidbody;
    Seek seek;

    void update(float dt)
    {
        rigidbody.integrate(position,dt);
        seek.update(*this);
    }

    void draw()
    {
        sfwl::drawBox(position.x, position.y, 8, YELLOW);
        sfwl::drawLine(position.x, position.y,
            position.x + rigidbody.velocity.x,
            position.y + rigidbody.velocity.y);

        //sfwl::drawBox(seek.target.x, seek.target.y, 8, YELLOW);

        for (unsigned i = 0; i+1 < seek.waypoints.size(); ++i)
        {
            sfwl::drawLine(seek.waypoints[i].x, seek.waypoints[i].y,
                           seek.waypoints[i + 1].x, seek.waypoints[i+1].y, YELLOW);
        }

        sfwl::drawLine(position.x,position.y,seek.waypoints[seek.current].x, seek.waypoints[seek.current].y, GREEN);
    }
};

inline void Seek::update(Agent &a)
{
    if (waypoints.empty() || distance(a.position, waypoints.back()) < 25)
    {
        current = 0;

        waypoints = solver->SolveAll(
            graph->FindNode(a.position, distance)->index,
            graph->FindNode(Vector2::random({ 800,600 }), distance)->index);
    }

    float curDis = distance(a.position, waypoints[current]);
    float nexDis = current < waypoints.size() - 1 ? distance(a.position, waypoints[current + 1]) : FLT_MAX;

    if ( curDis < 25 || nexDis < curDis)
        current++;

    a.rigidbody.addForce((waypoints[current] - a.position) * 1900);
}