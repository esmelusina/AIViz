#pragma once

#include "Graph.h"
#include "sfwl.h"

struct Agent;

struct Seek
{
    Vector2 target;

    // Randomly select new target position if too close.
    // Otherwise, addForce in direction of target.
    void update(Agent &a);    
};

struct Agent
{
    Vector2 position;
    Vector2 force;
    Vector2 acceleration;
    Vector2 velocity;

    void addForce(const Vector2 &f);  //increase the forces
    void integrate(float dt);        // Integrate force over accel, accel over velocity, velocity over position

    Seek seek;

    void update(float dt)
    {
        integrate(dt);
        seek.update(*this);
    }

    void draw()
    {
        sfwl::drawBox(position.x, position.y, 8, RED);
        sfwl::drawLine(position.x, position.y,
            position.x + velocity.x, position.y + velocity.y);
    }
};