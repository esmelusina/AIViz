
#include "sfwl.h"
#include "Agent.h"
#include "Behaviors.h"

void main()
{
    sfwl::initContext();

    Agent sally;

    sally.position    = {400,300};
    sally.maxRunSpeed = 100;

    //    float radius, distance, jitter;    
    Wander wander = Wander{50,50,10};

    while (sfwl::stepContext())
    {
        sally.update(sfwl::getDeltaTime());

        wander.update(sally);

        sally.draw();
    }

    sfwl::termContext();
}