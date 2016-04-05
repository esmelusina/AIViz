#include "sfwl.h"
#include "agent.h"
#include "Graph.h"
#include "Solver.h"

inline float Heuristic(const Vector2 &a, const Vector2 &b)
{
    return fabsf(a.x - b.x) + fabsf(a.y - b.y);
}

inline bool  Comparison1(const Meta &a, const Meta &b)
{
    return a.f <  b.f;
}

int main()
{
    sfwl::initContext();
    Graph<Vector2> *pGraph = makeGrid({ 80,60 }, { 720,540 }, 16, 16);

    std::vector<Vector2> dat = pGraph->getData();
    std::vector<float> mat = pGraph->getMatrix();

    Solver<Vector2> st(dat.size(), dat, mat, Comparison1, Heuristic);

    Agent sally, bob, molly;

    sally.seek.graph  = pGraph;
    sally.seek.solver = &st;

    bob.seek.graph = pGraph;
    bob.seek.solver = &st;

    molly.seek.graph = pGraph;
    molly.seek.solver = &st;

    sally.position = { 400, 300 };
    bob.position   = { 400, 300 };
    molly.position = { 400, 300 };
    while (sfwl::stepContext())
    {
        sally.update(sfwl::getDeltaTime());
        bob.update(sfwl::getDeltaTime());
        molly.update(sfwl::getDeltaTime());

        molly.draw();
        sally.draw();
        bob.draw();
    }

    sfwl::termContext();
}