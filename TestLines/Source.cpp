#include "sfwl.h"
#include <random>
#include <iostream>

#include "Grid.h"
#include "Solver.h"

bool comparison(const Solver<Vector2>::Meta &a, const Solver<Vector2>::Meta &b)
{
    return a.f < b.f;
}

int main(int argc, char **argv)
{
    Grid2D myGrid(4, 4, {100,100}, {200,200});

    Solver<Vector2> st(4, myGrid.node_data, myGrid.edge_data, comparison, distance);
        
    sfwl::initContext();

    while (sfwl::stepContext())
    {
        for (unsigned i = 0; i < myGrid.size; ++i)
            sfwl::drawBox(myGrid.node_data[i].x, myGrid.node_data[i].y, 8);

        for (unsigned i = 0; i < myGrid.size; ++i)
            for (unsigned j = 0; j < myGrid.size; ++j)
                if (myGrid.edge_data[i*myGrid.size + j])
                {
                    sfwl::drawLine(myGrid.node_data[i].x, myGrid.node_data[i].y, 
                                   myGrid.node_data[j].x, myGrid.node_data[j].y );
                }
        {

        }
    }

    sfwl::termContext();


    //st.doSearch(0, 3);
    //while (!st.step());

    //auto r = st.getPath();
    return 0;
};