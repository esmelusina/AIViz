#pragma once
#include "Agent.h"




struct Flee
{
    Vector2 *e_target;
    void update(Agent &a);
};

struct Seek 
{
    Vector2 *e_target;
    void update(Agent &a);
};

struct Wander
{
    float radius, distance, jitter;
    Vector2 target;

    void update(Agent &a);
};

