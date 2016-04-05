#pragma once
#include "Vector2.h"

class Rigidbody 
{
public:
    float mass;

    Vector2 velocity, acceleration, force, jerk;
    float terminalVelocity;
    float drag;


    Rigidbody() :
        acceleration({ 0,0 }), velocity({ 0,0 }), mass(1),
        force({ 0,0 }), drag(0), terminalVelocity(100)
    {

    }

    void addForce(const Vector2 &f)
    {
        force = force + f;
    }

    void Rigidbody::integrate(Vector2 &p, float dt)
    {

        jerk = force / mass - acceleration; // Jerk is optional!
        acceleration = acceleration + jerk * dt; // acceleration = force/mass;
        velocity = velocity + acceleration * dt;

        //if (velocity.magnitude() > terminalVelocity)
          //  velocity = normal(velocity) * terminalVelocity;

        p = p + velocity * dt;

        velocity = velocity - velocity * drag * dt;
        force = { 0, 0 };
    }
};