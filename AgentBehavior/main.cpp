
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

    while (sfwl::stepContext())
    {
        sally.update(sfwl::getDeltaTime());


        sally.draw();
    }

    sfwl::termContext();
}