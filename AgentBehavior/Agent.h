#pragma once
#include "sfwl.h"
#include "Rigidbody.h"


struct Agent
{
    Vector2 position;
    float maxRunSpeed;
    Rigidbody rigidbody;
    

    void update(float dt)
    {
        rigidbody.integrate(position,dt);
    }

    void draw()
    {
        sfwl::drawBox(position.x, position.y, 8, YELLOW);
        sfwl::drawLine(position.x, position.y,
            position.x + rigidbody.velocity.x,
            position.y + rigidbody.velocity.y);
    }
};