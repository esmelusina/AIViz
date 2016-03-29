#include "sfwl.h"
#include "visualize.h"
#include <iostream>


void main()
{
    sfwl::initContext();


    // node positions
    float    x[5]  = {100,200,300,100,300};
    float    y[5]  = {100,100,100,200,200};

    // node paintings
    unsigned c[5]  = {GREEN,GREEN,GREEN,CYAN,CYAN};
   
    // adjacency matrix
    float    a[25] = {
                        0,0,0,1,1,
                        0,0,0,1,1,
                        0,0,0,1,1,
                        1,1,1,0,0,
                        1,1,1,0,0
                     };

    while (sfwl::stepContext())
    {
        drawGraph(5,x,y,c,a);
    }

    sfwl::termContext();
}