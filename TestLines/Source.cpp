#include "sfwl.h"
#include <random>
#include <iostream>
#include <cmath>
#include <random>
#include "Graph.h"
#include "Solver.h"

inline void drawSolver(const Solver<Vector2> &s)
{
    for (unsigned i = 0; i < s.size; ++i)
    {
        unsigned color;
        switch (s.meta_data[i].state)
        {
        case Meta::undiscovered: color = BLUE; break;
        case Meta::frontier:     color = CYAN; break;
        case Meta::explored:     color = 0x888888ff; break;
        }

        switch (s.meta_data[i].path)
        {
        case Meta::start:   color = GREEN;   break;
        case Meta::goal:    color = MAGENTA; break;
        case Meta::route:   color = YELLOW;  break;
        }

        sfwl::drawBox(s.node_data[i].x, s.node_data[i].y, 8, color);
    }

}



inline float Heuristic(const Vector2 &a, const Vector2 &b)
{
    return fabsf(a.x-b.x) + fabsf(a.y-b.y);
}

inline bool  Comparison(const Meta &a,const Meta &b)
{
    return a.DOS > b.DOS;
}


int main(int argc, char **argv)
{
    Graph<Vector2> *pGraph = makeGrid({0,0}, {800,600}, 32, 32);

    std::vector<Vector2> dat = pGraph->getData();
    std::vector<float> mat = pGraph->getMatrix();
    
    delete pGraph;

    Solver<Vector2> st(dat.size(), dat, mat, Comparison, Heuristic);
  
    
    sfwl::initContext();

    
    unsigned start = rand() % st.size;
    unsigned goal  = rand() % st.size;
    st.doSearch(start, goal);

    bool solved = false;
    float timer = 0;
    //float delay = .01f;
    do
    {
        timer += sfwl::getDeltaTime();

        if(timer > 0.0f)
        {
            
            if (st.step() && !solved)
            {               
                st.getPath();
                solved = true;
                timer = 0;
            }
            else if(!solved)  timer = 0;
            
            if(timer > 2.1f)
            {
                solved = false;
                timer = 0;
                start = goal;
                goal = rand() % st.size;
                st.doSearch(start, goal);
            }                    
        }

        drawSolver(st);
    } while (sfwl::stepContext());

    sfwl::termContext();
    return 0;
};