#pragma once

#include "Graph.h"

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

    /*
    Position

        RigidBody properties
            - Force
            - Acceleration
            - Velocity
            - addForce(Vector2)

        update
            - update Seek

        draw
            - Draw a box or something at the position
    */
};