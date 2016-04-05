#include "Behaviors.h"
#include "Agent.h"


void Flee::update(Agent &a)
{

}

void Wander::update(Agent &a)
{
    //target = 
    //Vector2::fromAngle(rand())*radius +
    //Vector2::fromAngle(rand())*jitter;

    //target = normal(target) * radius;

    //target = target + normal(a.rigidbody.velocity)*distance;
}

void Seek::update(Agent &a)
{

}