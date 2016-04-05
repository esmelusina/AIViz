#include "Behaviors.h"
#include "Agent.h"


void Flee::update(Agent &a)
{

}

void Wander::update(Agent &a)
{
    target = 
    Vector2::fromAngle(rand())*radius +
    Vector2::fromAngle(rand())*jitter;

    target = normal(target) * radius;

    if(a.rigidbody.velocity.magnitude() > 0)
        target = target + normal(a.rigidbody.velocity)*distance;

    else
        target = target + Vector2::fromAngle(rand())*distance;


    Vector2 force = normal(target) * a.maxRunSpeed;

    a.rigidbody.addForce(force);
}

void Seek::update(Agent &a)
{

}