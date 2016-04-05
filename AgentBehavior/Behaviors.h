#pragma once
#include "Agent.h"

struct Behavior
{
    virtual void update(Agent &a) = 0;
};


struct Flee : Behavior
{
    Vector2 *e_target;
    void update(Agent &a);
};

struct Seek : Behavior
{
    Vector2 *e_target;
    void update(Agent &a);
};

struct Wander : Behavior
{
    float radius, distance, jitter;
    Vector2 target;

    void update(Agent &a);
};

